/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multi_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:03:20 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 14:03:21 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	multi_execve(t_data *data, int index)
{
	char	*path;
	t_cmd	cmd;
	int		status;

	cmd = data->commands[index];
	path = get_path(data, cmd.name);
	if (!path)
		path = cmd.name;
	execve(path, cmd.args, data->envp);
	status = set_error(cmd.name);
	free_data(data);
	exit(status);
}

int	multi_child(t_data *data, int index)
{
	t_cmd		cmd;
	t_builtin	f_builtin;

	cmd = data->commands[index];
	f_builtin = is_builtin(cmd.name);
	if (!cmd.name)
		exit(EXIT_SUCCESS);
	if (!f_builtin)
		multi_execve(data, index);
	else
		data->status = builtin_child(f_builtin, data, index);
	exit(data->status);
}

void	exec_child(t_data *data, int fd_in, int index)
{
	if ((index + 1) != data->n_cmd)
		close(data->pipe_fd[READ]);
	if (fd_in != -1)
		data->commands[index].fd_in = fd_in;
	data->commands[index].fd_out = data->pipe_fd[WRITE];
	if ((index + 1) == data->n_cmd)
		data->commands[index].fd_out = STDOUT_FILENO;
	if (redir_check(data->commands + index))
		set_fds(data, index);
	if (redir_in(data, index) == -1)
	{
		error_msg("Error", "Redir in", NULL);
		exit(data->status);
	}
	if (!is_builtin(data->commands[index].name))
	{
		if (redir_out(data, index) == -1)
		{
			error_msg("Error", "Redir out", NULL);
			exit(data->status);
		}
	}
	multi_child(data, index);
}

int	exec_multiple(t_data *data)
{
	int	exit_status;
	int	status;

	status = 0;
	data->pid = init_pipes(data, -1, 0);
	if (data->pid == -1)
		return (STATUS_KO);
	waitpid(data->pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		status = WEXITSTATUS(exit_status);
	while (wait(NULL) != -1)
		;
	return (status);
}

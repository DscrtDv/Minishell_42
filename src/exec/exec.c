/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:02:11 by tim           #+#    #+#                 */
/*   Updated: 2023/11/10 16:52:49 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_sig_check(int exit_status, bool nl)
{
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGINT)
		{
			if (nl)
				printf("\n");
			return (130);
		}
		if (WTERMSIG(exit_status) == SIGQUIT)
			return (131);
	}
	return (EXIT_FAILURE);
}

t_builtin	is_builtin(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (f_echo);
	if (!ft_strcmp(name, "pwd"))
		return (f_pwd);
	if (!ft_strcmp(name, "cd"))
		return (f_cd);
	if (!ft_strcmp(name, "env"))
		return (f_env);
	if (!ft_strcmp(name, "export"))
		return (f_export);
	if (!ft_strcmp(name, "unset"))
		return (f_unset);
	if (!ft_strcmp(name, "exit"))
		return (f_exit);
	return (NULL);
}

int	exec_builtin(t_data *data, int index, t_builtin f_builtin)
{
	if (redir_check(data->commands + index))
		if (redir_type(data, index) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (f_builtin(data, index));
}

int	exec_bin(t_data *data)
{
	int	exit_status;

	init_signals(PARENT);
	data->pid = fork();
	if (data->pid < 0)
		return (error_msg("fork failed", NULL, NULL), EXIT_FAILURE);
	if (data->pid == 0)
	{
		init_signals(CHILD);
		exec_single(data);
	}
	waitpid(data->pid, &exit_status, 0);
	init_signals(NORMAL);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (ft_sig_check(exit_status, true));
}

int	init_exec(t_data *data)
{
	int		i;
	int		status;

	i = 0;
	while (i < data->n_cmd)
	{
		data->commands[i].fd_in = STDIN_FILENO;
		data->commands[i].fd_out = STDOUT_FILENO;
		i++;
	}
	status = handle_hd(data);
	if (status != 0)
		return (status);
	if (data->n_cmd == 1)
		status = exec_simple(data);
	else
		status = exec_multiple(data);
	clean_hds(data);
	return (status);
}

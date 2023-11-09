/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multi_exec_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:02:06 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 14:05:49 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && (unsigned)s1[i] == (unsigned)s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static void	close_pipe(int *fd)
{
	close(fd[WRITE]);
	close(fd[READ]);
}

static int	parent_fds(t_data *data, int prev_fd, int index)
{
	if ((index + 1) < data->n_cmd)
		if (close(data->pipe_fd[WRITE]) == -1)
			return (EXIT_FAILURE);
	if (prev_fd != -1)
		if (close(prev_fd) == -1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	builtin_child(t_builtin f_builtin, t_data *data, int index)
{
	return (f_builtin(data, index));
}

int	init_pipes(t_data *data, int prev_fd, int index)
{
	pid_t	pid;

	if ((index + 1) < data->n_cmd)
	{
		if (pipe(data->pipe_fd) == -1)
			return (error_msg("Broken pipe", NULL, NULL), -1);
	}
	init_signals(PARENT);
	pid = fork();
	if (pid == -1)
		return (close_pipe(data->pipe_fd), \
				error_msg("fork", NULL, NULL), -1);
	if (pid == 0)
	{
		init_signals(CHILD);
		exec_child(data, prev_fd, index);
	}
	init_signals(NORMAL);
	if (parent_fds(data, prev_fd, index))
		return (EXIT_FAILURE);
	if ((index + 1) == data->n_cmd)
		return (pid);
	return (init_pipes(data, data->pipe_fd[READ], index + 1));
}

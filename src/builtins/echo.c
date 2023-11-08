/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 13:59:23 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 13:59:25 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	echo_check(char *av)
{
	if (*av == '\0' || (*av != '-' && *++av != 'n'))
		return (0);
	av++;
	while (*av == 'n')
		av++;
	if (*av == '\0')
		return (1);
	return (0);
}

static void	echo_write(t_cmd *cmd, char **av, int flag)
{
	while (*av)
	{
		ft_putstr_fd(*av, cmd->fd_out);
		av++;
		if (*av)
			ft_putstr_fd(" ", cmd->fd_out);
	}
	if (!flag)
		ft_putstr_fd("\n", cmd->fd_out);
}

int	f_echo(t_data *data, int index)
{
	char	**av;
	t_cmd	*cmd;
	int		flag;

	cmd = &(data->commands[index]);
	flag = 0;
	av = cmd->args;
	av++;
	while (*av)
	{
		if (!echo_check(*av))
		{
			if (**av == '\0')
				av++;
			break ;
		}
		flag = 1;
		av++;
	}
	echo_write(cmd, av, flag);
	return (EXIT_SUCCESS);
}

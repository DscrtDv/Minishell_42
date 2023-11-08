/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 13:59:03 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 13:59:06 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_pwd(t_data *data, int index)
{
	char	cwd[MAXPATHLEN];
	t_cmd	*cmd;

	cmd = data->commands + index;
	if (getcwd(cwd, MAXPATHLEN))
		ft_putstr_fd(cwd, cmd->fd_out);
	else
		return (1);
	ft_putstr_fd("\n", cmd->fd_out);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 13:58:55 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 13:58:57 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_unset(t_data *data, int index)
{
	t_cmd	*cmd;
	int		i;

	cmd = &(data->commands[index]);
	i = 1;
	while (i < cmd->n_args)
	{
		pop(data, cmd->args[i]);
		i++;
	}
	return (STATUS_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 13:59:11 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 13:59:13 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	export_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (ft_isdigit(str[i]))
		return (false);
	if (ft_strlen(str) == 1 && *str == '=')
		return (false);
	while (str[i] && str && str[i] != '=')
	{
		if (str[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

static int	handle_no_equal(t_data *data, t_cmd *cmd, int i)
{
	char	*key;
	char	*val;

	key = ft_substr(cmd->args[i], 0, -1);
	if (!key)
		return (MEM_ERR);
	val = malloc(sizeof(char) * 1);
	if (!val)
		return (free(key), MEM_ERR);
	val[0] = '\0';
	if (!export_check(key))
		return (free(key), free(val), STATUS_KO);
	else
	{
		update_env(data, key, val);
		return (free(key), free(val), STATUS_OK);
	}
}

static int	export_env(t_data *data, t_cmd *cmd, int i, int pos)
{
	char	*key;
	char	*val;

	key = ft_substr(cmd->args[i], 0, pos);
	if (!key)
		return (malloc_protect(data), MEM_ERR);
	val = ft_substr(cmd->args[i], (pos + 1), ft_strlen(cmd->args[i]));
	if (!val)
		return (free(key), malloc_protect(data), MEM_ERR);
	if (update_env(data, key, val) == MEM_ERR)
		return (free(key), free(val), malloc_protect(data), MEM_ERR);
	return (free(key), free(val), STATUS_OK);
}

static int	export_loop(t_data *data, t_cmd *cmd)
{
	int		pos;
	int		i;

	i = 1;
	while (i < cmd->n_args)
	{
		pos = find_equal(cmd->args[i]);
		if (pos != -1 && export_check(cmd->args[i]))
			data->status = export_env(data, cmd, i, pos);
		else if (pos == -1)
			data->status = handle_no_equal(data, cmd, i);
		else if (!export_check(cmd->args[i]))
			data->status = EXIT_FAILURE;
		i++;
	}
	if (data->status == MEM_ERR)
		return (malloc_protect(data), MEM_ERR);
	if (data->status == EXIT_FAILURE)
		error_msg("export", cmd->args[i - 1], "not a valid identifier");
	return (data->status);
}

int	f_export(t_data *data, int index)
{
	t_cmd	*cmd;

	cmd = &(data->commands[index]);
	data->status = STATUS_OK;
	if (cmd->n_args == 1)
	{
		print_env(data, index, false);
		return (data->status);
	}
	return (export_loop(data, cmd));
}

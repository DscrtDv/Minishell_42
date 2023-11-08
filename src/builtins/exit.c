/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 13:59:17 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 13:59:19 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	exit_check(char *str)
{
	if (!is_numeric(str))
		return (false);
	return (true);
}

static int	compute_code(char *str)
{
	int	sign;
	int	num;
	int	tmp;
	int	res;

	sign = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	num = ft_atoi(str);
	if (sign)
	{
		tmp = num / 256;
		res = 256 - (num - (tmp * 256));
	}
	else
		res = num;
	return (res);
}

static int	exit_with_code(t_data *data, t_cmd *cmd)
{
	int	status;

	status = STATUS_OK;
	if (cmd->n_args == 2)
	{
		status = compute_code(cmd->args[1]);
		free_data(data);
		ft_putstr_fd("exit\n", 1);
		exit(status);
	}
	else
		return (error_msg("exit", "too many arguments", NULL), \
		EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	f_exit(t_data *data, int index)
{
	t_cmd	*cmd;

	cmd = data->commands + index;
	if (cmd->n_args == 1)
	{
		free_data(data);
		ft_putstr_fd("exit\n", 1);
		exit (EXIT_SUCCESS);
	}
	if (!exit_check(cmd->args[1]))
	{
		error_msg("exit", cmd->args[1], "numeric argument required");
		return (2);
	}
	else
		return (exit_with_code(data, cmd));
}

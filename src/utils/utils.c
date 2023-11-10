/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 10:16:17 by rares         #+#    #+#                 */
/*   Updated: 2023/11/10 17:10:40 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	raise_error(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int	get_end_token_index(char *input, int i)
{
	while (input[i])
	{
		i++;
		if ((ft_strchr(" <>", input[i]) != 0)
			&& (not_in_quotes(input, i) == true))
			return (i);
	}
	return (i);
}

bool	correct_dollar(t_data *data)
{
	int		i;
	char	*input;

	i = 0;
	input = data->input;
	while (input[i])
	{
		if (input[i] == '$' && (not_in_single_quotes(input, i) == true))
		{
			i++;
			if (input[i] && (input[i] == '$'
					&& (not_in_single_quotes(input, i) == true)))
			{
				printf("Syntax error: Unexpected token '$' \n");
				return (false);
			}
		}
		if (input[i])
			i++;
	}
	return (true);
}

void	get_n_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->input && data->input[i])
	{
		if (data->input[i] == '|' && not_in_quotes(data->input, i) == true)
			data->n_cmd++;
		i++;
	}
}

bool	contains_only_quotes(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str && str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			flag++;
		i++;
	}
	if (flag != 0)
		return (false);
	return (true);
}

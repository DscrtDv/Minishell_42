/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check_1.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 10:11:53 by rares         #+#    #+#                 */
/*   Updated: 2023/11/09 15:40:57 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	correct_pipes(t_data *data)
{
	int		i;
	int		j;
	char	*input;

	i = 0;
	j = 0;
	input = data->input;
	while (ft_isspace(input[i]) == 1)
		i++;
	if (input[i] == '|' && not_in_quotes(input, i) == true)
		return (false);
	while (input[i])
	{
		if (input[i] == '|' && not_in_quotes(input, i) == true)
		{
			j = i + 1;
			while ((input[j] != '\0') && (ft_isspace(input[j]) == 1))
				j++;
			if ((input[j] == '|') || (input[j] == '\0'))
				return (false);
		}
		i++;
	}
	return (true);
}

static bool	correct_redir_out(char *input, int i)
{
	int	j;

	j = i + 1;
	if (input[j] == '>')
		j++;
	while ((input[j] != '\0') && (ft_isspace(input[j]) == 1))
	{
		j++;
	}
	if (input[j] == '>')
	{
		printf("Syntax error: Unexpected token '>'\n");
		return (false);
	}
	if (input[j] == '<')
	{
		printf("Syntax error: Unexpected token '<'\n");
		return (false);
	}
	if (input[j] == '\0')
	{
		printf("Syntax error: Unexpected token '>'\n");
		return (false);
	}
	return (true);
}

static bool	correct_redir_in(char *input, int i)
{
	int	j;

	j = i + 1;
	if (input[j] == '<')
		j++;
	while ((input[j] != '\0') && (ft_isspace(input[j]) == 1))
	{
		j++;
	}
	if (input[j] == '<')
	{
		printf("Syntax error: Unexpected token '<'\n");
		return (false);
	}
	if (input[j] == '>')
	{
		printf("Syntax error: Unexpected token '>'\n");
		return (false);
	}
	if (input[j] == '\0')
	{
		printf("Syntax error: Unexpected token '<'\n");
		return (false);
	}
	return (true);
}

bool	correct_redir(t_data *data)
{
	int		i;
	char	*input;

	i = 0;
	input = data->input;
	while (input[i])
	{
		if ((input[i] == '>') && (not_in_quotes(input, i) == true))
		{
			if (correct_redir_out(input, i) == false)
				return (false);
		}
		if ((input[i] == '<') && (not_in_quotes(input, i) == true))
		{
			if (correct_redir_in(input, i) == false)
				return (false);
		}
		i++;
	}
	return (true);
}

int	check_syntax(t_data *data)
{
	if (closed_quotes(data) == false)
	{
		printf("Syntax error: Unclosed quotes detected\n");
		*g_exit_code = 258;
		return (-1);
	}
	if (correct_pipes(data) == false)
	{
		printf("Syntax error: Unexpected token '|'\n");
		*g_exit_code = 258;
		return (-1);
	}
	if (correct_redir(data) == false)
	{
		*g_exit_code = 258;
		return (-1);
	}
	if (correct_dollar(data) == false)
	{
		*g_exit_code = 258;
		return (-1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_4.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 10:24:10 by rares         #+#    #+#                 */
/*   Updated: 2023/11/09 13:11:52 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_start_env_key(char *input, int *i, int *j, int *var_len)
{
	if (input[*i] == '{')
		(*i)++;
	*var_len = 0;
	*j = *i;
}

static int	append_check_1(t_exp_data *exp, char *str, int i)
{
	if (exp->env_value != NULL && ((str[i] == '}'
				&& (str[exp->start] == '$' && str[exp->start + 1] == '{'
					&& curly_braces_closed(str, i) == false))))
	{
		return (1);
	}
	if (exp->dollar_out == false && (exp->env_value != NULL && ((str[i] == '}'
					&& (str[exp->start] == '{' && str[exp->start + 1] == '$'
						&& curly_braces_closed(str, i) == false)))))
	{
		return (1);
	}
	return (0);
}

static int	append_check_2(t_exp_data *exp, char *str, int i)
{
	if (exp->env_value == NULL
		&& (str[i] == '}' && str[exp->start] == '$' && str[i - 1] != '\"'))
	{
		if (i > 0 && (str[exp->start + 1] == '\"'
				|| str[exp->start + 1] == '\''))
		{
			return (0);
		}
		return (1);
	}
	if ((str[i] == '?' && (i > 0 && str[i - 1] == '$'))
		&& not_in_single_quotes(str, i) == true)
	{
		return (1);
	}
	return (0);
}

int	append_check(t_exp_data *exp, char *str, int i)
{
	if (append_check_1(exp, str, i) != 0)
		return (1);
	if (append_check_2(exp, str, i) != 0)
		return (1);
	return (0);
}

char	*allocate_new_str(char *str, char *value, int start, int end)
{
	int		i;
	int		j;
	size_t	x;
	int		len_key;
	char	*new_str;

	len_key = end - start + 1;
	new_str = malloc(sizeof(char)
			* (ft_strlen(str) - len_key + ft_strlen(value) + 2));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	x = 0;
	while (str && str[i] && str[i] != '$')
		new_str[j++] = str[i++];
	while (x < ft_strlen(value))
		new_str[j++] = value[x++];
	new_str[j] = '\0';
	return (new_str);
}

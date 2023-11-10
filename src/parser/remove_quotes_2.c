/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 10:08:09 by rares         #+#    #+#                 */
/*   Updated: 2023/11/10 17:11:11 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	single_quotes_found(char **clean_str, char **new_str, \
								char *str, int *i)
{
	int		index_l;
	int		index_r;

	init_quotes_indexes(i, &index_l, &index_r);
	while (str[*i] != '\0' && str[*i] != '\'')
		(*i)++;
	index_r = *i;
	*clean_str = ft_substr(str, index_l + 1, index_r - index_l - 1);
	if (*clean_str == NULL)
	{
		if (*new_str[0] != '\0')
			free(*new_str);
		return (-1);
	}
	*new_str = ft_join(*new_str, *clean_str);
	if (*new_str == NULL)
	{
		free(*clean_str);
		return (-1);
	}
	free(*clean_str);
	return (index_r);
}

static int	double_quotes_found(char **clean_str, char **new_str, \
								char *str, int *i)
{
	int		index_l;
	int		index_r;

	init_quotes_indexes(i, &index_l, &index_r);
	while (str[*i] != '\0' && str[*i] != '\"')
		(*i)++;
	index_r = *i;
	*clean_str = ft_substr(str, index_l + 1, index_r - index_l - 1);
	if (*clean_str == NULL)
	{
		if (*new_str[0] != '\0')
			free(*new_str);
		return (-1);
	}
	*new_str = ft_join(*new_str, *clean_str);
	if (*new_str == NULL)
	{
		free(*clean_str);
		return (-1);
	}
	free(*clean_str);
	return (index_r);
}

static int	no_quotes_found(char **clean_str, char **new_str, char *str, int *i)
{
	*clean_str = ft_substr(str, *i, 1);
	if (*clean_str == NULL)
	{
		if (*new_str[0] != '\0')
			free(*new_str);
		return (-1);
	}
	*new_str = ft_join(*new_str, *clean_str);
	if (*new_str == NULL)
	{
		free(*clean_str);
		return (-1);
	}
	free(*clean_str);
	return (0);
}

static void	free_new_str(char **new_str)
{
	if (*new_str != NULL && *new_str[0] != '\0')
		free(*new_str);
}

int	remove_quote_selector(char *str, char **clean_str, char **new_str, int *i)
{
	int	index_r;

	index_r = 0;
	if (str[*i] == '\'')
	{
		index_r = single_quotes_found(clean_str, new_str, str, i);
		if (index_r == -1)
			return (free_new_str(new_str), -1);
	}
	else if (str[*i] == '\"')
	{
		index_r = double_quotes_found(clean_str, new_str, str, i);
		if (index_r == -1)
			return (free_new_str(new_str), -1);
	}
	else
	{
		index_r = no_quotes_found(clean_str, new_str, str, i);
		if (index_r == -1)
			return (free_new_str(new_str), -1);
	}
	return (index_r);
}

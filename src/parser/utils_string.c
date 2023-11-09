/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_string.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 10:11:18 by rares         #+#    #+#                 */
/*   Updated: 2023/11/09 10:11:44 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

char	*ft_join(char *s1, char const *s2)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
	{
		if (s1 != NULL && s1[0] != '\0')
			free(s1);
		return (NULL);
	}
	ft_strlcpy(result, s1, len + 1);
	ft_strlcat(result, s2, len + 1);
	if (s1[0] != '\0')
	{
		free(s1);
		s1 = NULL;
	}
	return (result);
}

char	*ft_append_char(char *str, char c)
{
	size_t			i;
	size_t			j;
	char			*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (new_str == NULL)
	{
		if (str[0] != '\0')
			free(str);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (i < ft_strlen(str))
		new_str[j++] = str[i++];
	if (c != '\0')
		new_str[j] = c;
	new_str[++j] = '\0';
	if (str[0] != '\0')
	{
		free(str);
		str = NULL;
	}
	return (new_str);
}

char	*ft_dup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	if (s[0] == '\0')
	{
		dup = malloc (sizeof(char));
		dup[0] = '\0';
		return (dup);
	}
	else
		dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (s && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	_lstsize(t_token *lst)
{
	int		size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

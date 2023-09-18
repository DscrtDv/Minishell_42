/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 13:04:09 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/20 13:09:33 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

int	checkset(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*start;
	char	*end;

	if (!s1 || !set)
		return (0);
	start = (char *) s1;
	end = start + ft_strlen(s1);
	while (*start && checkset(*start, set))
		start++;
	while (end > start && checkset(*(end - 1), set))
		end--;
	return (ft_substr(start, 0, end - start));
}

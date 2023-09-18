/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:29:32 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/21 11:03:13 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n_len;
	size_t	index;

	n_len = ft_strlen(needle);
	index = 0;
	if (haystack == needle || !n_len)
		return ((char *)haystack);
	while (haystack[index] && index < len)
	{
		i = 0;
		while (needle[i] && haystack[index + i] == needle[i] && index + i < len)
			++i;
		if (i == n_len)
			return ((char *)haystack + index);
		++index;
	}
	return (NULL);
}

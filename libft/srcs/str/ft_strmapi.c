/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 13:29:53 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/21 13:39:14 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

size_t	ft_strlen(const char *str);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	index;

	result = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (0);
	index = 0;
	while (s[index])
	{
		result[index] = (*f)(index, s[index]);
		++index;
	}
	result[index++] = '\0';
	return (result);
}

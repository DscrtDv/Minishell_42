/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 13:02:00 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/20 13:02:33 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
	{
		len = 0;
		start = 0;
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub_s = malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (NULL);
	ft_strlcpy(sub_s, s + start, len + 1);
	return (sub_s);
}

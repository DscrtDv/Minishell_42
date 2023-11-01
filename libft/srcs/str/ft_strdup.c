/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 13:00:40 by tcensier      #+#    #+#                 */
/*   Updated: 2023/10/30 18:21:01 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	len;

	len = ft_strlen(s) + 1;
	p = malloc(sizeof(char) * len);
	if (!p)
		return (0);
	ft_strlcpy(p, s, len);
	return (p);
}

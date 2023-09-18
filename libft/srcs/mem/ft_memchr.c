/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:01:13 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/13 16:12:37 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *) s;
	while (n--)
	{
		if (*temp != (unsigned char) c)
			temp++;
		else
			return (temp);
	}
	return (0);
}

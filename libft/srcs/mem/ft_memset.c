/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 12:43:46 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/07 16:04:54 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;

	temp = s;
	while (n--)
		*temp++ = (unsigned char) c;
	return (s);
}

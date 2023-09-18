/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:53:43 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/13 16:11:37 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *) s1;
	t2 = (unsigned char *) s2;
	while (n && (*t1 == *t2))
	{
		t1++;
		t2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*t1 - *t2);
}

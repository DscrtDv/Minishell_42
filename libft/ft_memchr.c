/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 11:50:26 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 15:48:29 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*c_s;

	c_s = (unsigned char *)s;
	while (n > 0)
	{
		if (*c_s == (unsigned char)c)
		{
			return ((void *)c_s);
		}	
		c_s++;
		n--;
	}
	return (0);
}

// int main(void)
// {
// 	char str[] = "123456";
// 	printf("Own:  %s\n", ft_memchr(str, '3', 5));
// 	printf("Real: %s\n", memchr(str, '3', 5));
// }

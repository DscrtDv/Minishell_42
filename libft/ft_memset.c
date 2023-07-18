/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 16:05:59 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/16 16:07:44 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *s, int value, size_t len)
{
	unsigned char	*x;

	x = (unsigned char *)s;
	while (len > 0)
	{
		*x = value;
		x++;
		len--;
	}
	return ((void *)s);
}

// int	main(void)
// {

// 	char str1[] = "123456789";
// 	char str2[] = "123456789";

// 	ft_memset(str1, 'A', 2);
// 	memset(str2, 'A', 2);
//     printf("Own:   %s\n", str1);
// 	printf("Real:  %s\n", str2);
// }

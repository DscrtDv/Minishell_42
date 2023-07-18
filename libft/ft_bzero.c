/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 17:21:09 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/16 13:17:00 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*x;

	x = (unsigned char *)s;
	while (n > 0)
	{
		*x = '\0';
		x++;
		n--;
	}
}

// int	main(void)
// {
// 	char		str[] = "123456789";
// 	char		str1[] = "123456789";
// 	int			i = 0;

// 	ft_bzero(str, 10);
// 	bzero(str1, 10);
// 	int len = 10;
// 	while (len != 0)
// 	{
// 		printf("%d%d\n", str[i], str1[i]);
// 		len--;
// 		i++;
// 	}
// }

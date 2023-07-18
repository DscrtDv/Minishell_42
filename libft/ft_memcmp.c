/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 15:30:08 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 15:48:50 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*c_s1;
	const unsigned char	*c_s2;

	c_s1 = (const unsigned char *)s1;
	c_s2 = (const unsigned char *)s2;
	while (n > 0)
	{
		if (*c_s1 > *c_s2)
		{
			return (*c_s1 - *c_s2);
		}
		if (*c_s1 < *c_s2)
		{
			return (*c_s1 - *c_s2);
		}
		n--;
		c_s1++;
		c_s2++;
	}
	return (0);
}

// int main(void)
// {
// 	char *s1 = "AAA";
// 	char *s2 = " AAA";

// 	printf("Own:  %d\n", ft_memcmp(s1, s2, 5));
// 	printf("Real: %d\n", ft_memcmp(s1, s2, 5));
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 11:50:56 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 13:02:27 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 > *s2)
		{
			return ((unsigned char)*s1 -(unsigned char)*s2);
		}
		else if (*s1 < *s2)
		{
			return ((unsigned char)*s1 -(unsigned char)*s2);
		}
		else if (*s1 == '\0' || *s2 == '\0')
		{
			return ((*s1 - 1) - (*s2 - 1));
		}
		n--;
		s1++;
		s2++;
	}
	return (0);
}

// int main(void)
// {
// 	char *s1 = "atoms \0";
//  	char *s2 = "atomsa ";

// 	printf("Own:   %d\n", ft_strncmp(s1, s2, 8));
// 	printf("Real:  %d\n", strncmp(s1, s2, 8));
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 18:50:06 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/16 19:05:35 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// static void	test(unsigned int i, char *c)
// {	
// 	i = 0;
// 	while (i < 1)
// 	{
// 		*c = 'X';
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	char	s[50] = "111111111111111";
// 	ft_striteri(s, test);
// 	printf("%s\n", s);
// }
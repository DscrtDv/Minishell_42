/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 13:29:45 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 15:49:46 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 32;
	}
	return (c);
}

// int main(void)
// {
// 	char str[10] = "aaaAAA";
// 	int count;
// 	char letter;

// 	count = 0;
// 	letter = 'A';

// 	while (str[count])
// 	{
// 		ft_tolower(letter);
// 		str[count] = letter;
// 		count++;
// 	}
// 	printf("%s\n", str);
// }

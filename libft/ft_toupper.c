/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 17:30:35 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 15:50:09 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
	}
	return (c);
}

// int main(void)
// {
// 	//char str[] = "AAAaaa";

// 	char str[] = "AAAaaa";
// 	//str = "AAAaaa"
// 	char letter = 'a';
// 	int count = 0;

// 	while(str[count])
// 	{
// 		ft_toupper(letter);
// 		str[count] = letter;
// 		count++;
// 	}
// 	printf("%s\n", str);
// }
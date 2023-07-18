/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 13:35:26 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/11 13:38:45 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_isalnum(int a)
{
	return (ft_isalpha(a) || ft_isdigit(a));
}

// int	main(void)
// {
// 	printf("%d\n", ft_isalnum('z'));
// 	printf("%d\n", ft_isalnum('1'));
// 	printf("%d\n", ft_isalnum(' '));
// }
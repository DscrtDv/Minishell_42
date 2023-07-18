/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 12:28:36 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/16 16:08:55 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	number;

	number = n;
	if (number < 0)
	{
		number *= -1;
		write (fd, "-", 1);
	}
	if (number >= 0 && number <= 9)
	{
		number += '0';
		write (fd, &number, 1);
	}
	else
	{
		ft_putnbr_fd((number / 10), fd);
		ft_putnbr_fd((number % 10), fd);
	}
}

// int	main(void)
// {
// 	ft_putnbr_fd(2147483647, 2);
// 
// }

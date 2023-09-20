/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_put.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:41:04 by tcensier      #+#    #+#                 */
/*   Updated: 2022/11/03 10:47:42 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(1, str, len);
}

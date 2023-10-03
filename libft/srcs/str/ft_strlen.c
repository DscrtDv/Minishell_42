/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 12:40:24 by tcensier      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/10/07 16:04:04 by tcensier      ########   odam.nl         */
=======
/*   Updated: 2023/09/20 16:59:18 by rares         ########   odam.nl         */
>>>>>>> origin/rares
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

<<<<<<< HEAD
size_t	ft_strlen(const char *str)
{
	size_t	len;
=======

int	ft_strlen(const char *str)
{
	int	len;
>>>>>>> origin/rares

	len = 0;
	while (str[len])
		len++;
	return (len);
}

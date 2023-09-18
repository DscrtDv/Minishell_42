/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 14:03:40 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/20 17:31:27 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stddef.h>

static size_t	intlen(long int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t		len;
	char		*result;
	long int	temp_n;

	temp_n = (long int) n;
	len = intlen(temp_n);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	if (temp_n < 0)
	{
		result[0] = '-';
		temp_n *= -1;
	}
	if (temp_n == 0)
		result[0] = '0';
	result[len] = '\0';
	while (temp_n)
	{
		result[len - 1] = temp_n % 10 + '0';
		temp_n /= 10;
		len--;
	}
	return (result);
}

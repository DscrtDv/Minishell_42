/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   num_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 10:36:36 by tcensier      #+#    #+#                 */
/*   Updated: 2022/11/03 10:37:16 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	ulong_len(long long n, unsigned long base)
{
	size_t	len;

	len = 0;
	if (n == 0)
		len++;
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_itoabase(long long n, char *set, unsigned long base, int sign)
{
	size_t	len;
	char	*result;

	if (n < 0 && sign)
		n *= -1;
	len = ulong_len(n, base) + sign;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (n == 0)
		result[0] = '0';
	else if (sign == 1)
		result[0] = '-';
	result[len] = '\0';
	while (n)
	{
		result[len - 1] = set[(unsigned)n % base];
		n /= base;
		len--;
	}
	return (result);
}

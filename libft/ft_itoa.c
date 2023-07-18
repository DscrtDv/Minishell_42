/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 13:59:51 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 13:38:49 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	len_int(int n)
{
	long int	nr;
	int			len;

	nr = n;
	len = 0;
	if (nr <= 0)
	{
		len++;
		nr *= -1;
	}
	while (nr > 0)
	{
		nr = nr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len_n;
	char		*n_str;
	long int	nr;

	nr = n;
	len_n = len_int(nr);
	n_str = malloc(sizeof(char) * (len_n + 1));
	if (n_str == NULL)
		return (NULL);
	if (nr < 0)
	{
		n_str[0] = '-';
		nr *= -1;
	}
	n_str[len_n] = '\0';
	if (nr == 0)
		n_str[0] = '0';
	while (nr > 0)
	{
		n_str[len_n - 1] = (nr % 10) + '0';
		nr = nr / 10;
		len_n--;
	}
	return (n_str);
}

// int	main(void)
// {
// 	int	n = 0;
// 	char *result;
// 	result = ft_itoa(n);
// 	printf("%s\n", result);
// }
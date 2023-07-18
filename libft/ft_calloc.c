/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:41:18 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/16 13:34:40 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc (count * size);
	if (p == NULL)
		return (p);
	ft_bzero(p, count * size);
	return (p);
}

// int	main(void)
// {
// 	char	*array;
// 	int		i;

// 	i = 0;
// 	array = calloc(5, 4);
// 	array[0] = 10;
// 	array[1] = 10;
// 	while (i < 5)
// 	{
// 		printf("%d\n", array[i]);
// 		i++;
// 	}
// }

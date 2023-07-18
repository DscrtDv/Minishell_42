/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 15:30:42 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 14:03:36 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*cast_dest;
	const char	*cast_src;

	cast_dest = (char *)dest;
	cast_src = (const char *)src;
	if (cast_dest == NULL && cast_src == NULL)
	{
		return (NULL);
	}
	while (n > 0)
	{
		*cast_dest = *cast_src;
		n--;
		cast_src++;
		cast_dest++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char src[] = "123456789";
// 	char *dst = src + 2;

// 	ft_memcpy(dst, src, 5);
// 	printf("%s\n\n", src);
// }

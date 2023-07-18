/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:41:11 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 13:39:56 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (((dstsize - 1) > i) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
	{
		i++;
	}
	return (i);
}

// int main()
// {
// 	char real_dst[10];
// 	char real_src[10] = "12345678";
// 	int real_res;

// 	char own_dst[10];
// 	char own_src[10] = "12345678";
// 	int own_res;

// 	own_res = ft_strlcpy(own_dst, own_src, sizeof(own_dst));
// 	real_res = strlcpy(real_dst, real_src, sizeof(real_dst));

// 	printf(" Own: %s\n",   own_dst);
// 	printf(" Own: %d\n\n", own_res);

// 	printf("Real: %s\n",  real_dst);
// 	printf("Real: %d\n",  real_res);
// // }

// int main(void)
// {
// 	char *dest;
// 	ft_print_result(ft_strlcpy(dest, "lorem ipsum dolor sit amet", 15));
//     write(1, "\n", 1);
//     write(1, dest, 15);
// }

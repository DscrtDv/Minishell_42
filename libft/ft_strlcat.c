/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 16:10:51 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 13:12:00 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strlcat(char *dst, const char *src, size_t dst_size)
{
	size_t	i_src;
	size_t	i_dst;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i_src = 0;
	i_dst = dst_len;
	if (dst_size <= dst_len || dst_size == 0)
	{
		return (dst_size + src_len);
	}
	while (src[i_src] && dst_len + i_src < dst_size - 1)
	{
		dst[i_dst] = src[i_src];
		i_src++;
		i_dst++;
	}
	dst[i_dst] = '\0';
	return (dst_len + src_len);
}

// int	main(void)
// {
// 	char dst1[14] = "a";
// 	char src1[] = "lorem ipsum dolor sit amet";

// 	char dst2[14] = "a";
// 	char src2[] = "lorem ipsum dolor sit amet";

// 	int own_res;
// 	int real_res;

// 	own_res = ft_strlcat(dst1, src1, 15);
// 	real_res = strlcat(dst2, src2, 15);

// 	printf("Own res:  %d\n", own_res);
// 	printf("Own dst:  %s\n\n", dst1);

// 	printf("Real res:  %d\n", real_res);
// 	printf("Real dst:  %s\n", dst2);
// }

/* if (dst_len < size - 1 && size > 0)
	{
		while (src[i_src])
		{
			dst[dst_len] = src[i_src];
			dst_len++;
			i_src++;
			
			if(dst_len == size - 1)
			{
				break;
			}
		}
		dst[dst_len] = '\0';
	}
	if (dst_len >= size)
	{
		dst_len = size;
	} 
	return (dst_len + src_len); */
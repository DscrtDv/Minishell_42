/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/6/14 16:57:25 by raanghel      #+#    #+#                 */
/*   Updated: 2022/6/18 12:22:33 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	st_copy_lr(char *c_dst, char *c_src, size_t len)
{
	while (len > 0)
	{
		*c_dst = *c_src;
		c_dst--;
		c_src--;
		len--;
	}
}

static void	st_copy_rl(char *c_dst, char *c_src, size_t len)
{
	while (len > 0)
	{
		*c_dst = *c_src;
		c_dst++;
		c_src++;
		len--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*c_dst;
	char	*c_src;

	c_dst = (char *)dst;
	c_src = (char *)src;
	if ((c_dst == NULL) && (c_src == NULL))
	{
		return (NULL);
	}
	if (src < dst)
	{
		c_dst += len - 1;
		c_src += len - 1;
		st_copy_lr(c_dst, c_src, len);
	}
	else
		st_copy_rl(c_dst, c_src, len);
	return (dst);
}

// int	main(void)
// {
// 	char src[] = "123456789";
// 	//char *dst = src + 2;

// 	ft_memmove(src, src, 5);
// 	printf("%s\n\n", src);
// }

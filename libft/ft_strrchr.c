/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 12:20:38 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 13:40:28 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = ft_strlen(str);
	str += len;
	while (len >= 0)
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str--;
		len--;
	}
	return (0);
}

// int main(void)
// {
// 	char *str = "bbabbbbabb";
// 	printf("Own:  %s\n", ft_strrchr(str, 'a'));
// 	printf("Real: %s\n", strrchr(str, 'a'));
// }

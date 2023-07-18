/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:30:18 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 13:20:09 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
	{
		return ((char *)haystack);
	}
	while (i < len && haystack[i])
	{
		j = 0;
		while (needle[j] && (i + j) < len)
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	*s1 = "sdfds FIND THIS  df grg4g   ";
//  	char	*s2 = "FIND THIS";

// 	printf("Own:  %s\n", ft_strnstr(s1, s2, 50));
// 	printf("Real: %s\n", strnstr(s1, s2, 50));
// }

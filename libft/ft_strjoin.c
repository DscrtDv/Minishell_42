/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 13:15:40 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 13:39:47 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len_s3;
	char	*s3;

	i = 0;
	j = 0;
	len_s3 = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc((len_s3 + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i] = s2[j];
		j++;
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

// int	main(void)
// {
// 	char s1[] = "JOIN ";
// 	char s2[] = "THIS!";

// 	//s1[0] = 0;
// 	//s2[0] = 0;

// 	printf("%s\n", ft_strjoin(s1, s2));
// 	//printf("%s\n", strjoin(s1, s2));

// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 14:12:07 by raanghel      #+#    #+#                 */
/*   Updated: 2023/09/08 18:32:15 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// int	main(void)
// {
// 	char *s = "Baaam!";
// 	char *res1;
// 	char *res2;

// 	res1 = ft_strdup(s);
// 	res2 = strdup(s);
// 	printf("Own:  %s\n", res1);
// 	printf("Real: %s\n", res2);
// }

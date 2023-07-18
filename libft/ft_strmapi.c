/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 17:17:32 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 13:40:10 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fresh_s;
	unsigned int	i;
	int				len_s;

	if (s == NULL)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	fresh_s = malloc (sizeof(char) * (len_s + 1));
	if (fresh_s == NULL)
	{
		return (NULL);
	}
	while (s[i])
	{
		fresh_s[i] = f(i, s[i]);
		i++;
	}
	fresh_s[i] = '\0';
	return (fresh_s);
}

// static char	test(unsigned int i, char c)
// {
// 	char	new_c;

// 	new_c = c;
// 	if (i % 2 == 0 && c >= 'a' && c <= 'z')
// 		new_c -= 32;
// 	return (new_c);
// }

// static char test (unsigned int i, char c)
// {	
// 	while (i <= 5)
// 	{	
// 		c = 'X';
// 		i--;
// 	}
// 	return (c);
// }

// int main(void)
// {
// 	char *str;
// 	str = ft_strmapi("aaaaaaaaa", test);
// 	printf("%s\n", str);
// }

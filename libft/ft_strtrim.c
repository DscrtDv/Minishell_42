/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:49:20 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 13:40:37 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	find_c(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	find_start(int start, char const *s1, char const *set)
{
	while (s1[start])
	{
		if (find_c(s1[start], set) == 1)
			start++;
		else
			break ;
	}
	return (start);
}

static int	find_end(int end, int start, char const *s1, char const *set)
{
	while (end > start)
	{
		if (find_c(s1[end - 1], set) == 1)
			end--;
		else
			break ;
	}
	return (end);
}

char	*ft_strtrim(char const	*s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*trimed_str;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	start = find_start(start, s1, set);
	end = find_end(end, start, s1, set);
	trimed_str = malloc(sizeof(char) * (end - start + 1));
	if (trimed_str == NULL)
		return (NULL);
	while (start < end)
	{
		trimed_str[i] = s1[start];
		i++;
		start++;
	}
	trimed_str[i] = '\0';
	return (trimed_str);
}

// int main(void)
// {
// 	char *s1 = "XY0YYYXXX00Y";
// 	char *set = "YX";

// 	printf("%s\n", ft_strtrim(s1, set));
// }

// static char	find_c(char c, char const *set)
// {
// 	int	i;

// 	i = 0;
// 	while (set[i])
// 	{
// 		if (set[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	*ft_strtrim(char const	*s1, char const *set)
// {
// 	int		start;
// 	int		end;
// 	int		i;
// 	char	*trimed_str;

// 	start = 0;
// 	end = ft_strlen(s1);
// 	i = 0;
// 	while (s1[start])
// 	{
// 		if (find_c(s1[start], set) == 1)
// 			start++;
// 		else
// 			break ;
// 	}
// 	while (end > start)
// 	{
// 		if (find_c(s1[end - 1], set) == 1)
// 			end--;
// 		else
// 			break ;
// 	}
// 	trimed_str = malloc(sizeof(char) * (end - start + 1));
// 	if (trimed_str == NULL)
// 		return (NULL);
// 	while (start < end)
// 	{
// 		trimed_str[i] = s1[start];
// 		i++;
// 		start++;
// 	}
// 	trimed_str[i] = '\0';
// 	return (trimed_str);
// }

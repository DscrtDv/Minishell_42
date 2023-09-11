/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 11:23:57 by raanghel      #+#    #+#                 */
/*   Updated: 2023/09/07 09:20:35 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	_sub_str_count(char const *s, char c)
{
	int	i;
	int	len_s;
	int	count;

	i = 0;
	count = 0;
	len_s = ft_strlen(s);
	while (s[i] == c)
		i++;
	while (i < len_s)
	{
		if (s[i] != c)
			i++;
		if (s[i] == c && s[i] != '\0')
		{
			count++;
			i++;
		}
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	if (i > 0 && s[len_s - 1] != c)
		count++;
	return (count);
}

static int	_sub_str_len(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != c)
	{
		if (s[i] != c)
			len++;
		i++;
		if (s[i] == '\0')
			break ;
	}
	return (len);
}

void	_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free (matrix);
}

static char	**process(char **str_split, char const *s, char c)
{
	int	row;
	int	i;

	i = 0;
	row = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			str_split[row] = ft_substr(s, i, _sub_str_len((s + i), c));
			if (str_split[row] == NULL)
			{
				_free(str_split);
				return (NULL);
			}
			row++;
			i = i + _sub_str_len((s + i), c);
		}
		else
			i++;
	}
	str_split[row] = NULL;
	return (str_split);
}

char	**ft_split(char	const *s, char c)
{
	char	**str_split;
	int		nr_of_substr;

	nr_of_substr = _sub_str_count(s, c);
	str_split = (char **)malloc (sizeof(char *) * (nr_of_substr + 1));
	if (str_split == NULL)
		return (NULL);
	str_split = process(str_split, s, c);
	return (str_split);
}

// int	main(void)
// {
// 	char	**result;
// 	int		i;

// 	i = 0;
// 	result = ft_split("nonempty", '\0');
// 	while (result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		i++;
// 	}
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 11:39:13 by tcensier      #+#    #+#                 */
/*   Updated: 2023/09/22 16:08:00 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	temp;

	temp = c;
	while (*s != temp)
		if (*s++ == '\0')
			return (0);
	return ((char *)s);
}

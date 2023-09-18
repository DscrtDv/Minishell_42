/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 11:39:13 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/22 13:04:20 by tcensier      ########   odam.nl         */
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

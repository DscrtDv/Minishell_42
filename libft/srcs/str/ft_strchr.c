/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 13:10:05 by tcensier      #+#    #+#                 */
/*   Updated: 2023/11/09 13:10:08 by tcensier      ########   odam.nl         */
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

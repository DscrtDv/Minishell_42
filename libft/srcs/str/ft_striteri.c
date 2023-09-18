/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 13:40:33 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/21 18:18:58 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	index;

	if (!s)
		return ;
	index = 0;
	while (s[index])
	{
		(*f)(index, &s[index]);
		++index;
	}
}

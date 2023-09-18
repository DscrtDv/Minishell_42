/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 13:02:47 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/21 14:59:18 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(size * nmemb);
	if (!p)
		return (0);
	ft_bzero(p, size * nmemb);
	return (p);
}

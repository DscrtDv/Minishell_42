/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 14:44:37 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/21 14:59:25 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstadd_front(l_list **lst, l_list *new)
{
	new->next = *lst;
	*lst = new;
}

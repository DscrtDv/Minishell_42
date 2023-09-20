/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 17:23:26 by tcensier      #+#    #+#                 */
/*   Updated: 2022/10/21 17:52:12 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear(l_list **lst, void (*del)(void *))
{
	l_list	*temp;
	l_list	*to_del;

	temp = *lst;
	while (temp)
	{
		to_del = temp;
		temp = temp->next;
		ft_lstdelone(to_del, del);
	}
	*lst = NULL;
}

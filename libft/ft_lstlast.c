/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 17:19:41 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/16 13:54:41 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// int	main(void)
// {
// 	char s[] = "YEA! You found me!";

// 	t_list	*first;
// 	t_list	*second;
// 	t_list	*third;
// 	t_list	*fourth;
// 	t_list	*last;
// 	t_list	*ret;

// 	first = malloc (sizeof(t_list));
// 	second = malloc (sizeof(t_list));
// 	third = malloc (sizeof(t_list));
// 	fourth = malloc (sizeof(t_list));
// 	last = malloc (sizeof(t_list));

// 	first->next = second;
// 	second->next = third;
// 	third->next = fourth;
// 	fourth->next = last;
// 	last->next = NULL;

// 	last->content = s;

// 	ret = ft_lstlast(first);
// 	printf("Last node says: %s", ret->content);
// }
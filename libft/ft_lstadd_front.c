/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 16:34:45 by raanghel      #+#    #+#                 */
/*   Updated: 2023/07/12 14:19:16 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	char *content_1 = "Rares";
// 	char *content_2 = "Baaam!";

// 	t_list *first = ft_lstnew(content_1);
// 	t_list *second = ft_lstnew(content_2);
// 	ft_lstadd_front(&first, second);

// 	printf("%s\n", first->content);
// }
// 	//t_list	*temp = first;
// // 	while (first != NULL)
// // 	{
// // 		printf("%s\n", first->content);
// // 		first = first->next;
// // 	}
// // }

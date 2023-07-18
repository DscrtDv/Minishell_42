/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 15:56:35 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/18 15:25:36 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

// int	main(void)
// {
// 	char	content_1[] = "First";
// 	char	content_2[] = "Second";
// 	char	content_3[] = "Third";
// 	int		nr_of_nodes;

// 	t_list	*first;
// 	t_list	*second;
// 	t_list	*third;

// 	first = malloc (sizeof(t_list));
// 	second = malloc (sizeof(t_list));
// 	third = malloc (sizeof(t_list));

// 	first->content = content_1;
// 	first->next = second;

// 	second->content = content_2;
// 	second->next = third;

// 	third->content = content_3;
// 	third->next = NULL;

// 	nr_of_nodes = ft_lstsize(first);
// 	printf("Number of nodes: %d\n", nr_of_nodes);
// }

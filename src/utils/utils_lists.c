/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_lists.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 10:15:18 by rares         #+#    #+#                 */
/*   Updated: 2023/11/09 13:02:27 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(char *word)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->str = word;
	new_token->type = -1;
	new_token->next = NULL;
	return (new_token);
}

t_token	*get_to_last_node(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	insert_at_end(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = get_to_last_node(*lst);
	if (temp == NULL)
		return ;
	temp->next = new;
}

// void free_env_list(t_env *env)
// {
// 	t_env	*temp;
// 	while (temp != NULL)
// 	{
// 		temp = env;
// 		env = env->next;	
// 		free(temp->key);
// 		free(temp->val);
// 		free (temp);
// 	}
// }

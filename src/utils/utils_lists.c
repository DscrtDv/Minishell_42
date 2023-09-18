int	malloc_calls;
int free_cals;
#include"../../include/minishell.h"

t_token	*create_token(char *word)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	malloc_calls++;
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

void insert_at_end(t_token **lst, t_token *new)
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
	temp->next = new;
}

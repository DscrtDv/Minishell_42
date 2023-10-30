#include"../../include/minishell.h"

t_token	*create_token(char *word) //malloc protected
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	//new_token = NULL;
	printf("word: %s\n", word);
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

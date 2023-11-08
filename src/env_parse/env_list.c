/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:00:23 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 14:00:25 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pop(t_data *data, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *(data->env);
	prev = NULL;
	if (curr != NULL && !ft_strcmp(curr->key, key))
	{
		*(data->env) = curr->next;
		free_node(curr);
		return (STATUS_OK);
	}
	while (curr != NULL && ft_strcmp(curr->key, key))
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return (STATUS_KO);
	prev->next = curr->next;
	free_node(curr);
	return (STATUS_OK);
}

t_env	*new_node(char *key, char *val)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node), NULL);
	node->val = ft_strdup(val);
	if (!node->val)
		return (free(node->key), free(node), NULL);
	node->next = NULL;
	return (node);
}

t_env	*create_node(t_data *data, char *envp, int pos)
{
	char	*val;
	char	*key;
	t_env	*node;

	(void)data;
	if (pos)
	{
		key = ft_substr(envp, 0, pos);
		if (!key)
			malloc_protect(data);
		val = ft_substr(envp, pos + 1, ft_strlen(envp));
		if (!val)
		{
			free(key);
			malloc_protect(data);
		}
		node = new_node(key, val);
		if (!node)
			return (free(key), free(val), NULL);
		else
			return (free(key), free(val), node);
	}
	return (NULL);
}

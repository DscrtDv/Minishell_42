#include "../../include/minishell.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

static int	add_env(t_data *data, char *key, char *str)
{
	t_env	*node;

	node = *(data->env);
	while (node->next)
		node = node->next;
	node->next = new_node(key, str);
	if (!node->next)
		return (MEM_ERR);
	return (STATUS_OK);
}

int	update_env(t_data *data, char *key, char *str)
{
	t_env	*node;
	size_t	s_len;

	s_len = ft_strlen(str);
	node = *(data->env);
	while (node && ft_strcmp(node->key, key))
		node = node->next;
	if (node)
	{
		free(node->val);
		node->val = NULL;
		node->val = ft_substr(str, 0, s_len);
		if (!node->val)
			return (MEM_ERR);
	}
	else
		return (add_env(data, key, str));
	return (STATUS_OK);
}

char	*ft_getenv(t_data *data, char *key)
{
	t_env	*node;

	node = *(data->env);
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (node->val);
		node = node->next;
	}
	return (NULL);
}

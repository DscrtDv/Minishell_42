#include "../../include/minishell.h"

static t_env	*insert_node(t_data *data, char *envp)
{
	int		pos;
	t_env	*node;

	pos = find_equal(envp);
	node = create_node(data, envp, pos);
	return (node);
}

void	clear_list(t_env *node)
{
	t_env	*tmp;

	tmp = NULL;
	while (node)
	{
		tmp = node;
		node = node->next;
		free_node(tmp);
	}
}

int	save_env(t_data *data, char **envp, int size)
{
	int	i;

	i = 0;
	data->envp = malloc(sizeof(char *) * (size + 1));
	if (!data->envp)
		return (MEM_ERR);
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
			return (MEM_ERR);
		i++;
	}
	data->envp[i] = NULL;
	return (STATUS_OK);
}

static void	env_alloc(t_data *data)
{
	data->env = ft_calloc(sizeof(t_env *), 1);
	if (!data->env)
		malloc_protect(data);
}

void	envcpy(t_data *data, char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	i = 1;
	env_alloc(data);
	head = insert_node(data, envp[0]);
	if (!head)
		malloc_protect(data);
	node = head;
	while (envp[i])
	{
		node->next = insert_node(data, envp[i]);
		if (!node->next)
		{
			clear_list(head);
			malloc_protect(data);
		}
		node = node->next;
		i++;
	}
	if (save_env(data, envp, i) == MEM_ERR)
		return (clear_list(head), malloc_protect(data));
	*(data->env) = head;
}

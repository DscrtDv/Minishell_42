#include "../../include/minishell.h"

static t_env    *insert_node(t_data *data, char *envp)
{
    int     pos;
    t_env   *node;

    pos = find_equal(envp);
    node = create_node(data, envp, pos);
    return (node);
}

void    clear_list(t_env *node)
{
    t_env *tmp;

    tmp = NULL;
    while(node)
    {
        tmp = node;
        node = node->next;
        free_node(tmp);
    }
}

void    save_env(t_data *data, char **envp, int size)
{
    int i;

    i = 0;
    data->envp = malloc(sizeof(char *) * size);
    if (!data->envp)
        malloc_protect(data);
    while (envp[i])
    {
        data->envp[i] = ft_strdup(envp[i]);
        if (!data->envp[i])
            malloc_protect(data);
        i++;
    }
    data->envp[i] = NULL;
}

void    envcpy(t_data *data, char **envp)
{
    t_env    *head;
    t_env    *node;
    int      i;

    i = 1;
    data->env = ft_calloc(sizeof(t_env *), 1);
    if (!data->env)
        malloc_protect(data);
    head = insert_node(data, envp[0]);
    if (!head)
        malloc_protect(data);
    node = head;
    while (envp[i])
    {
        node->next = insert_node(data, envp[i]);
        // printf("inserting: %s\n%s\n", node->key, node->val);
        if (!node->next)
        {
            clear_list(head);
            malloc_protect(data);
        }
        node = node->next;
        i++;
    }
    save_env(data, envp, i);
    *(data->env) = head;
}
#include "../minishell.h"

static t_env    *insert_node(t_data *data, char *envp)
{
    int     pos;
    t_env   *node;

    pos = find_equal(envp);
    node = create_node(data, envp, pos);
    return (node);
}

void    envcpy(t_data *data, char **envp)
{
    t_env    *head;
    t_env    *node;
    int      i;

    i = 1;
    data->env = ft_calloc(sizeof(t_env *), 1);
    if (!data->env)
        return ;
    head = insert_node(data, envp[0]);
    //malloc protect
    if (!head)
        return ;
    node = head;
    while (envp[i])
    {
        node->next = insert_node(data, envp[i]);
        //malloc protect
        if (!node->next)
            return ;
        node = node->next;
        //printf("%s\n", envp[i]);
        i++;
    }
    *(data->env) = head;
    //print_list(data);
}

#include "../../include/minishell.h"

int    free_node(t_env *node)
{
    free(node->key);
    free(node->val);
    free(node);
    return (EXIT_SUCCESS);
}

int    free_list(t_env **env)
{
    t_env   *node;
    t_env   *temp;

    node = *env;
    while (node)
    {
        
        temp = node;
        node = node->next;
        if (ft_strcmp(temp->key, "?"))
            free_node(temp);
    }
    free(env);
    return (EXIT_SUCCESS);
}

int    free_cmd_struct(t_cmd *cmd)
{
    if (cmd->name)
        free(cmd->name);
    if (cmd->n_args)
        ft_free_array(cmd->args);
    return (EXIT_SUCCESS);
}

int	free_cmds(t_data *data)
{
    int i;
    i = 0;
    while (i < data->n_cmd)
    {
        free_cmd_struct(data->commands + i);
        i++;
    }
    data->commands = NULL;
    data->n_cmd = 0;
    return (EXIT_SUCCESS);
}

int    free_data(t_data *data)
{
    if (data->input)
        free(data->input);
    if (data->input_split_by_cmds)
        ft_free_array(data->input_split_by_cmds);
    if (data->env)
        free_list(data->env);
    /*
    if (data->envp)
        ft_free_array(data->envp);
    */
    if (data->commands)
        free_cmds(data);
    set_null(data);
    free(data);
    return (EXIT_SUCCESS);
}

void    malloc_protect(t_data *data)
{
    free_data(data);
    exit(137);
}


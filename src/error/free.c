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
    printf("Freeing list\n");
    t_env   *node;
    t_env   *temp;

    node = *env;
    while (node)
    {
        temp = node;
        node = node->next;
        free_node(temp);
    }
    free(env);
    return (EXIT_SUCCESS);
}

int    free_cmd_struct(t_cmd *cmd)
{
    if (cmd->cmd_name)
        free(cmd->cmd_name);
    if (cmd->cmd_args)
        ft_free_array(cmd->cmd_args);
    return (EXIT_SUCCESS);
}

/*
int     free_tokens(t_token *tokens)
{
    printf("Freeing tokens\n");
    t_token *temp;

    while (tokens)
    {
        temp = tokens;
        tokens = tokens->next;
        printf("Free: %s\n", temp->str);
        free(temp->str);
        free(temp);
    }
    //free(tokens);
    printf("freed Tokens\n");
    return (EXIT_SUCCESS);
}
*/

int    free_cmds(t_data *data)
{
    int i;
    printf("Freeing cmd\n");
    i = 0;
    while (i < data->cmd_count)
    {
        free_cmd_struct(data->commands + i);
        i++;
    }
    data->commands = NULL;
    data->cmd_count = 0;
    return (EXIT_SUCCESS);
}
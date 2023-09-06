#include "../../include/minishell.h"

int     find_equal(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (str[i] == '\0')
        return (0);
    return (i);
}

void    update_env(t_data *data, char *key, char *str)
{
    t_env *node;

    node = *(data->env);
    while (node && !ft_strcmp(node->key, key))
        node = node->next;
    if (node){
        node->val = str;
    }
}

char    *ft_getenv(t_data *data, char *key)
{
    t_env   *node;

    node = *(data->env);
    while (node)
    {
        if (!ft_strcmp(node->key, key))
            return (node->val);
        node = node->next;
    }
    return ("No env variable");
}

static t_env   *new_node(char *key, char *val)
{
    t_env   *node;

    node = malloc(sizeof(t_env));
    //malloc protect
    if (!node)
        return (NULL);
    node->key = key;
    node->val = val;
    node->next = NULL;

    return (node);
}

t_env   *create_node(t_data *data, char *envp, int pos)
{
    char    *val;
    char    *key;
    (void)data;

    if (pos)
    {
        key = ft_substr(envp, 0, pos);
        //malloc protect
        if (!key)
            return (NULL);
        val = ft_substr(envp, pos+1, ft_strlen(envp));
        //malloc protect
        if (!val)
            return (NULL);
    }
    return (new_node(key, val));
}
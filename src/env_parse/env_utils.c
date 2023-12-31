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

int     pop(t_data *data, char *key)
{
    t_env   *curr;
    t_env   *prev;
    
    curr = *(data->env);
    prev = NULL;
    if (curr != NULL && !ft_strcmp(curr->key, key))
    {
        *(data->env) = curr->next;
        free_node(curr);
        return (0);
    }
    while (curr != NULL && ft_strcmp(curr->key, key))
    {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL)
    {
        printf("Nothing to unset. \n");
        return (1);
    }
    prev->next = curr->next;
    free_node(curr);
    return (0);
}

static t_env   *new_node(char *key, char *val)
{
    t_env   *node;

    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    node->key = key;
    node->val = val;
    node->next = NULL;

    return (node);
}


static void add_env(t_data *data, char *key, char *str)
{
    t_env   *node;

    node = *(data->env);
    while (node->next)
        node = node->next;
    node->next = new_node(key, str);
    if (!node->next)
        malloc_protect(data);
}

void    update_env(t_data *data, char *key, char *str)
{
    t_env *node;
    size_t  s_len;

    s_len = ft_strlen(str);
    node = *(data->env);
    while (node && ft_strcmp(node->key, key))
        node = node->next;
    if (node){
        if (ft_strlen(node->val) > s_len)
            ft_strlcpy(node->val, str, s_len + 1);
        else
        {
            node->val = malloc(s_len + 1);
            if (!node->val)
                malloc_protect(data);
            ft_strlcpy(node->val, str, s_len + 1);
        }
    }
    else
        add_env(data, key, str);
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
    return (NULL);
}

t_env   *create_node(t_data *data, char *envp, int pos)
{
    char    *val;
    char    *key;
    (void)data;

    if (pos)
    {
        key = ft_substr(envp, 0, pos);
        if (!key)
            malloc_protect(data);
        val = ft_substr(envp, pos+1, ft_strlen(envp));
        if (!val)
        {
            free(key);
            malloc_protect(data);
        }
        return (new_node(key, val));
    }
    return (NULL);
}
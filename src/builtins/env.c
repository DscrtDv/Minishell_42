#include "../../include/minishell.h"

static void    print_list(t_data *data)
{
    t_env   *head;

    head = *(data->env);
    while (head)
    {
        printf("%s=%s\n", head->key, head->val);
        head = head->next;
    }
}

int     f_env(t_data *data)
{
    print_list(data);
    return (0);
}
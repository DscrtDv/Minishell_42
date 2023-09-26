#include "../../include/minishell.h"

void    print_env(t_data *data, int index)
{
    t_env   *head;
    t_cmd   *cmd;

    head = *(data->env);
    cmd = data->commands + index;
    while (head)
    {
        ft_putstr_fd(head->key, cmd->fd_out);
        ft_putchar_fd('=', cmd->fd_out);
        ft_putstr_fd(head->val, cmd->fd_out);
        ft_putchar_fd('\n', cmd->fd_out);
        head = head->next;
    }
}

int     f_env(t_data *data, int index)
{
    print_env(data, index);
    return (0);
}
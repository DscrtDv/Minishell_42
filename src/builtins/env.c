#include "../../include/minishell.h"

void    print_env(t_data *data, int index, bool is_env)
{
    t_env   *head;
    t_cmd   *cmd;

    head = *(data->env);
    cmd = data->commands + index;
    while (head)
    {
        //printf("%i\n",!(is_env && head->val[0] == '\0'));
        if (ft_strcmp(head->key, "?") && !(is_env && head->val[0] == '\0'))
        {
            ft_putstr_fd(head->key, cmd->fd_out);
            ft_putchar_fd('=', cmd->fd_out);
            ft_putstr_fd(head->val, cmd->fd_out);
            ft_putchar_fd('\n', cmd->fd_out);
        }
        head = head->next;
    }
}

int     f_env(t_data *data, int index)
{
    t_cmd *cmd;

    cmd = data->commands + index;
    if (cmd->n_args > 1)
        return (error_msg("env", "too many arguments.", NULL), STATUS_KO);
    print_env(data, index, true);
    return (0);
}
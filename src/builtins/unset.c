#include "../../include/minishell.h"

int     f_unset(t_data *data)
{
    t_cmd   *cmd;
    int     i;

    cmd = &(data->commands[0]);
    i = 1;
    while (i < cmd->n_args)
    {
        if (pop(data, cmd->args[i]))
            return (1);
        i++;
    }
    return (0);
}
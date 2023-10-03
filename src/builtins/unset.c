#include "../../include/minishell.h"

int     f_unset(t_data *data, int index)
{
    t_cmd   *cmd;
    int     i;

    cmd = &(data->commands[index]);
    i = 1;
    while (i < cmd->n_args)
    {
        pop(data, cmd->args[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}
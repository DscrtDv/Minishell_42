#include "../../include/minishell.h"

int     f_exit(t_data *data, int index)
{
    t_cmd *cmd;

    cmd = data->commands + index;
    if (cmd->n_args == 1)
    {
        free_data(data);
        exit(0);
    }
    return (1);
}
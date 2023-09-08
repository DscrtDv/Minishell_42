#include "../../include/minishell.h"

int     f_unset(t_data *data)
{
    t_cmd   *cmd;
    int     i;

    cmd = &(data->commands[0]);
    i = 0;
    while (i < cmd->cmd_args_count)
    {
        if (pop(data, cmd->cmd_args[i]))
            return (1);
        i++;
    }
    return (0);
}
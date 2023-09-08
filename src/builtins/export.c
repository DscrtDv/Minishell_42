#include "../../include/minishell.h"

int     f_export(t_data *data)
{
    int     pos;
    int     i;
    char    *val;
    char    *key;
    t_cmd   *cmd;

    i = 0;
    cmd = &(data->commands[0]);
    while (i < cmd->cmd_args_count)
    {
        pos = find_equal(cmd->cmd_args[i]);
        if (pos)
        {
            key = ft_substr(cmd->cmd_args[i], 0, pos);
            //malloc protect
            if (!key)
                return (1);
            val = ft_substr(cmd->cmd_args[i], pos+1, ft_strlen(cmd->cmd_args[i]));
            //malloc protect
            if (!val)
                return (free(key), 1);
            update_env(data, key, val);
        }
        i++;
    }
    return (0);
}
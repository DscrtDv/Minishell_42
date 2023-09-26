#include "../../include/minishell.h"

int     f_export(t_data *data, int index)
{
    int     pos;
    int     i;
    char    *val;
    char    *key;
    t_cmd   *cmd;

    i = 1;
    cmd = &(data->commands[index]);
    if (cmd->n_args == 1)
    {
        print_env(data, index);
        return (0);
    }
    printf("%i | %i\n", i, cmd->n_args);
    while (i < cmd->n_args)
    {
        pos = find_equal(cmd->args[i]);
        if (pos)
        {
            key = ft_substr(cmd->args[i], 0, pos);
            if (!key)
                malloc_protect(data);
            val = ft_substr(cmd->args[i], pos+1, ft_strlen(cmd->args[i]));
            if (!val)
                malloc_protect(data);
            update_env(data, key, val);
        }
        i++;
    }
    return (0);
}
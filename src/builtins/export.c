#include "../../include/minishell.h"

static bool    export_check(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (false);
    if (ft_isdigit(str[i]))
        return (false);
    if (ft_strlen(str) == 1 && *str == '=')
        return (false);
    while (str[i] && str && str[i] != '=')
    {
        if (str[i] == '-')
            return (false);
        i++;
    }
    return (true);
}

void    handle_no_equal(t_data *data, t_cmd *cmd, int i)
{
    char *key;
    char *val;

    key = ft_substr(cmd->args[i], 0, -1);
    if (!key)
        malloc_protect(data);
    val = malloc(sizeof(char) * 1);
    if (!val)
        malloc_protect(data);
    val[0] = '\0';
    update_env(data, key, val);
}

int     f_export(t_data *data, int index)
{
    int     pos;
    int     i;
    char    *val;
    char    *key;
    t_cmd   *cmd;

    i = 1;
    cmd = &(data->commands[index]);
    data->status = EXIT_SUCCESS;
    if (cmd->n_args == 1)
    {
        print_env(data, index, false);
        return (data->status);
    }
    while (i < cmd->n_args)
    {
        pos = find_equal(cmd->args[i]);
        if (pos != -1 && export_check(cmd->args[i]))
        {
            key = ft_substr(cmd->args[i], 0, pos);
            if (!key)
                malloc_protect(data);
            val = ft_substr(cmd->args[i], pos+1, ft_strlen(cmd->args[i]));
            if (!val)
                malloc_protect(data);
            update_env(data, key, val);
        }
        else if (pos == -1)
            handle_no_equal(data, cmd, i);
        else if (!export_check(cmd->args[i]))
            data->status = EXIT_FAILURE;
        i++;
    }
    if (data->status == EXIT_FAILURE)
        error_msg("export", cmd->args[i-1], "not a valid identifier");
    return (data->status);
}
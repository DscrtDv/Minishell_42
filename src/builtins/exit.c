#include "../../include/minishell.h"

static bool is_numeric(char *str)
{
    int i;
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (false);
        i++;
    }
    return (true);
}

static bool exit_check(char *str)
{
    if (!is_numeric(str))
        return (false);
    return (true);
}

int     compute_code(char *str)
{
    int sign;
    int num;
    int tmp;
    int res;

    sign = 0;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = 1;
        str++;
    }
    num = ft_atoi(str);
    if (sign)
    {
        tmp = num / 256;
        res = 256 - (num - (tmp * 256));
    }
    else
        res = num;
    return (res);
}

int     f_exit(t_data *data, int index)
{
    t_cmd *cmd;

    cmd = data->commands + index;
    if (cmd->n_args == 1)
    {
        free_data(data);
        exit (EXIT_SUCCESS);
    }
    if (!exit_check(cmd->args[1]))
    {   
        error_msg("exit: numeric argument required\n");
        return (2);
    }
    else 
    {
        if (cmd->n_args == 2)
        {
            data->status = compute_code(cmd->args[1]);
            exit(data->status);
        }
        else
            return (error_msg("exit: too many arguments\n"), EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
#include "../../include/minishell.h"

static int    echo_check(char *av)
{
    if (*av != '-' && *++av != 'n')
        return (0);
    av++;
    while (*av == 'n')
        av++;
    if (*av == '\0')
        return (1);
    return (0);
}

int     f_echo(t_data *data, int index)
{
    char    **av;
    t_cmd   *cmd;
    int    flag;
    
    cmd = &(data->commands[index]);
    flag = 0;
    av = cmd->args;

    av++;
    while (*av)
    {
        if (!echo_check(*av))
            break ;
        flag = 1;
        av++;
    }
    while (*av)
    {
        ft_putstr_fd(*av, cmd->fd_out);
        av++;
        if (*av)
            ft_putstr_fd(" ", cmd->fd_out);
    }
    if (!flag)
        ft_putstr_fd("\n", cmd->fd_out);
    return (EXIT_SUCCESS);
}
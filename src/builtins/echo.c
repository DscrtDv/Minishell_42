/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 18:39:32 by tcensier      #+#    #+#                 */
/*   Updated: 2023/09/14 15:11:21 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

int     f_echo(t_data *data)
{
    char    **av;
    t_cmd   *cmd;
    int    flag;
    
    cmd = &(data->commands[0]);
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
        ft_putstr_fd(*av, 1);
        av++;
        if (*av)
            ft_putstr_fd(" ", 1);
    }
    if (!flag)
        ft_putstr_fd("\n", 1);
    return (0);
}
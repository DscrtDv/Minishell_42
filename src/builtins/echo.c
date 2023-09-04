/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 18:39:32 by tcensier      #+#    #+#                 */
/*   Updated: 2023/09/02 13:08:31 by tim           ########   odam.nl         */
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

int     f_echo(t_simple_cmd *cmd)
{
    char    **av;
    int    flag;
    
    flag = 0;
    av = cmd->argv;
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
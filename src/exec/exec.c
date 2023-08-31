/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 18:42:35 by tcensier      #+#    #+#                 */
/*   Updated: 2023/08/31 17:47:38 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_builtin is_builtin(char *name)
{
    if (!ft_strcmp(name, "echo"))
        return (f_echo);
    if (!ft_strcmp(name, "pwd"))
        return (f_pwd);        
    /*
    if (!ft_strcmp(name, "cd"))
        return (true);
    if (!ft_strcmp(name, "export"))
        return (true);
    if (!ft_strcmp(name, "unset"))
        return (true);
    if (!ft_strcmp(name, "env"))
        return (true);
    if (!ft_strcmp(name, "exit"))
        return (true);
    return (false);
    */
    return (NULL);
}

int     exec_builtin(t_simple_cmd *cmd, t_builtin f_builtin)
{
    return (f_builtin(cmd));
}

static int  exec_simple(t_simple_cmd *cmd)
{
    t_builtin   f_builtin;
    
    f_builtin = is_builtin(cmd->cmd_name);
    
    if (f_builtin)
        return (exec_builtin(cmd, f_builtin));
    return (0);
}

int init_exec(t_simple_cmd *cmd)
{
    return (exec_simple(cmd));
}
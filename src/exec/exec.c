/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 18:42:35 by tcensier      #+#    #+#                 */
/*   Updated: 2023/09/08 14:40:07 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_builtin is_builtin(char *name)
{
    if (!ft_strcmp(name, "echo"))
        return (f_echo);
    if (!ft_strcmp(name, "pwd"))
        return (f_pwd);        
    if (!ft_strcmp(name, "cd"))
        return (f_cd);
    if (!ft_strcmp(name, "env"))
        return (f_env);
    if (!ft_strcmp(name, "export"))
        return (f_export);
    if (!ft_strcmp(name, "unset"))
        return (f_unset);
    /*
    if (!ft_strcmp(name, "exit"))
        return (true);
    return (false);
    */
    return (NULL);
}

int     exec_builtin(t_data *data, t_builtin f_builtin)
{
    return (f_builtin(data));
}

int     exec_cmd(t_data *data)
{
    
}

static int  exec_simple(t_data *data)
{
    t_builtin   f_builtin;
    
    f_builtin = is_builtin(data->commands[0].cmd_name);
    
    if (f_builtin)
        return (exec_builtin(data, f_builtin));
    else
        return (exec_cmd(data));
    return (0);
}

int init_exec(t_data *data)
{
    if (data->cmd_count == 1)
        return (exec_simple(data));
    return (0);
}
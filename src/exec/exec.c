/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 18:42:35 by tcensier      #+#    #+#                 */
/*   Updated: 2023/08/30 19:09:35 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



bool is_builtin(char *name)
{
    if (!strncmp(name, "echo", 4))
        return (true);
    if (!strncmp(name, "cd", 2))
        return (true);
    if (!strncmp(name, "pwd", 3))
        return (true);
    if (!strncmp(name, "export", 6))
        return (true);
    if (!strncmp(name, "unset", 5))
        return (true);
    if (!strncmp(name, "env", 3))
        return (true);
    if (!strncmp(name, "exit", 4))
        return (true);
    return (false);
}

int exec_builtin(t_cmd *cmd)
{
    
}

int exec_single(t_data *mini)
{
    t_cmd   *cmd;
    
    cmd = mini->cmd_list;
    if (is_builtin(cmd->cmd_name))
        return (exec_builtin(cmd));
}

void exec_cmd(t_data *mini)
{
    if (mini->cmd_count == 1)
        exec_single(mini);
    else
        return ;
}
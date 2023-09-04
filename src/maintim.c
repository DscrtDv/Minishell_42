/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 17:37:57 by tcensier      #+#    #+#                 */
/*   Updated: 2023/09/04 09:37:00 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void init_cmd(t_simple_cmd *cmd, char *cmd_name, uint32_t argc, char **argv)
{
    cmd->cmd_name = cmd_name;
    cmd->argc = argc;
    cmd->argv = &argv[1];
    cmd->next = NULL;
    cmd->prev_dir[0] = '\0';
    //printf("|cmd_name: %s | argc: %d | argv: %s|\n", cmd_name, argc, argv[2]);
}

int main(int argc, char **argv)
{
    ft_strlen("yes");
    t_simple_cmd    *cmd;
    cmd = malloc(sizeof(t_simple_cmd));
    if (!cmd)
        exit (1);
    init_cmd(cmd, argv[1], argc-1, argv);
    init_exec(cmd);
    return (0);
}
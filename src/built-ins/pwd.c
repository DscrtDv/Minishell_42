/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 17:37:39 by tcensier      #+#    #+#                 */
/*   Updated: 2023/08/31 17:57:18 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/param.h>

int     f_pwd(t_simple_cmd *cmd)
{
    char    cwd[MAXPATHLEN];
    
    (void)cmd;
    if (getcwd(cwd, MAXPATHLEN))
        ft_putstr_fd(cwd, 1);
    else
        return (1);
    ft_putstr_fd("\n", 1);
    
    return (0);
}
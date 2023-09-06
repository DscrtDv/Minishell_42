/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 17:37:39 by tcensier      #+#    #+#                 */
/*   Updated: 2023/09/06 19:34:01 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     f_pwd(t_data *data)
{
    char    cwd[MAXPATHLEN];
    
    (void)data;
    if (getcwd(cwd, MAXPATHLEN))
        ft_putstr_fd(cwd, 1);
    else
        return (1);
    ft_putstr_fd("\n", 1);
    
    return (0);
}
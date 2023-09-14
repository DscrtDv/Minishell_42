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
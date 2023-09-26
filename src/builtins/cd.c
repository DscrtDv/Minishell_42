#include "../../include/minishell.h"

int     f_cd(t_data *data, int index)
{
    char    curdir[MAXPATHLEN];
    char    *path;
    char    *oldpwd;
    t_cmd   *cmd;

    getcwd(curdir, MAXPATHLEN);
    oldpwd = ft_getenv(data, "OLDPWD");
    cmd = &(data->commands[index]);

    if (cmd->n_args == 0 || !ft_strcmp(cmd->args[1], "~"))
    {
        path = ft_getenv(data, "HOME");
        if (!path)
        {
            error_msg("cd: HOME not set\n");
            return (EXIT_FAILURE);
        }
    }
    else
        path = cmd->args[1];

    if (!ft_strcmp(path, "-"))
    {
        if (!oldpwd)
        {
            error_msg("cd: OLDPWD not set\n");
            return (EXIT_FAILURE);
        }
        path = oldpwd;
    }
    if (!ft_strcmp(path, getcwd(0, 0)))
        return (0);
    if (chdir(path)){
        error_msg("cd");
        return 1;
    }
    update_env(data, "OLDPWD", curdir);
    update_env(data, "PWD", getcwd(0, 0));
    return (EXIT_SUCCESS);
}
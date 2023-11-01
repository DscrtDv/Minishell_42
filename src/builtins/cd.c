#include "../../include/minishell.h"

int     f_cd(t_data *data, int index)
{
    char    curdir[MAXPATHLEN];
    char    *new_dir;
    char    *path;
    char    *oldpwd;
    t_cmd   *cmd;

    getcwd(curdir, MAXPATHLEN);
    oldpwd = ft_getenv(data, "OLDPWD");
    cmd = &(data->commands[index]);
    if (cmd->n_args > 2)
    {
        error_msg("cd", "too many arguments", NULL);
        return (STATUS_KO);
    }
    if (cmd->n_args == 1 || !ft_strcmp(cmd->args[1], "~"))
    {
        path = ft_getenv(data, "HOME");
        if (!path)
        {
            error_msg("cd", "HOME not set", NULL);
            return (free(oldpwd), STATUS_KO);
        }
    }
    else
        path = cmd->args[1];
    if (!ft_strcmp(path, "-"))
    {
        if (!oldpwd)
        {
            error_msg("cd", "OLDPWD not set", NULL);
            return (STATUS_KO);
        }
        path = oldpwd;
    }
    new_dir = getcwd(NULL, 0);
    if (!new_dir)
        return (malloc_protect(data), MEM_ERR);
    if (!ft_strcmp(path, new_dir))
        return (free(new_dir), EXIT_SUCCESS);
    if (chdir(path))
    {
        error_msg("cd", path, "No such file or directory");
        return (free(new_dir), STATUS_KO);
    }
    update_env(data, "OLDPWD", curdir);
    update_env(data, "PWD", new_dir);
    return (free(new_dir), STATUS_OK);
}
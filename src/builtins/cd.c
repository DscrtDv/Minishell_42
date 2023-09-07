#include "../../include/minishell.h"

int     f_cd(t_data *data)
{
    char    curdir[MAXPATHLEN];
    char    *path;
    char    *oldpwd;
    t_cmd   *cmd;

    getcwd(curdir, MAXPATHLEN);
    oldpwd = ft_getenv(data, "OLDPWD");
    cmd = &(data->commands[0]);

    if (cmd->cmd_args_count == 0 || !ft_strcmp(cmd->cmd_args[0], "~"))
        path = ft_getenv(data, "HOME");
    else
        path = cmd->cmd_args[0];

    if (!ft_strcmp(path, "-"))
    {
        if (!oldpwd)
        {
            printf("cd: ODLPWD not set\n");
            return (1);
        }
        path = oldpwd;
    }
    //printf("%s || %s\n", path, getcwd(0, 0));
    if (!ft_strcmp(path, getcwd(0, 0)))
        return (0);
    if (chdir(path)){
        perror("cd");
        return 1;
    }
    update_env(data, "OLDPWD", curdir);
    update_env(data, "PWD", getcwd(0, 0));
    return (0);
}
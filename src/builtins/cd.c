#include "../../include/minishell.h"

int     f_cd(t_data *data)
{
    //char    curdir[MAXPATHLEN];
    char    *path;
    char    *oldpwd;
    t_cmd   *cmd;

    oldpwd = ft_getenv(data, "OLDPWD");
    update_env(data, "OLDPWD", getcwd(0, 0));
    cmd = &(data->commands[0]);

    if (cmd->cmd_args_count == 0 || !ft_strcmp(cmd->cmd_args[0], "~"))
        path = ft_getenv(data, "HOME");
    else
        path = cmd->cmd_args[0];

    if (!ft_strcmp(path, "-"))
    {
        if (!oldpwd)
        {
            printf("No previous directory.\n");
            return (1);
        }
        path = oldpwd;
    }
    if (chdir(path)){
        printf("Syntax not supported %s\n", path);
        return 1;
    }
    update_env(data, "PWD", getcwd(0, 0));
    return (0);
}
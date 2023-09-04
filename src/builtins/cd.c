#include "../../include/minishell.h"

int     f_cd(t_cmd *cmd)
{
    char    curdir[MAXPATHLEN];
    //char    path[MAXPATHLEN];
    char    *path;
    path = NULL;
    //current dir might be unreachable
    /*
    if (!getcwd(curdir, sizeof(curdir)))
        *curdir = '\0';
    */
    if (!cmd->cmd_args[0])
        path = getenv("HOME");
    else
        path = cmd->cmd_args[0];
    //printf("%s\n", getenv("HOME"));
    /*
    if (!ft_strcmp(av, "-"))
    {
        printf("yes\n");
        if (cmd->prev_dir[0] == '\0')
        {
            printf("No previous directory.\n");
            return (1);
        }
        av = cmd->prev_dir;
    }
    */
    printf("happens here\n");

    if (chdir(path)){
        printf("Syntax not supported %s\n", path);
        return 1;
    }
    //ft_strlcpy(cmd->prev_dir, curdir, MAXPATHLEN);
    getcwd(curdir, sizeof(curdir));
    printf("Current dir: %s\n", curdir);
    return (0);
}
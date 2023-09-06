#include "../../include/minishell.h"

int     f_cd(t_cmd *cmd)
{
    //char    curdir[MAXPATHLEN];
    char    *path;

    //char    curdir[MAXcurdirLEN];
    //current dir might be unreachable
    /*
    if (!getcwd(curdir, sizeof(curdir)))
        *curdir = '\0';
    */
    
    if (cmd->cmd_args_count == 0 || !ft_strcmp(cmd->cmd_args[0], "~"))
        path = getenv("HOME");
    else
        path = cmd->cmd_args[0];

    /*
    if (!ft_strcmp(av, "-"))
    {
        if (cmd->prev_dir[0] == '\0')
        {
            printf("No previous directory.\n");
            return (1);
        }
        av = cmd->prev_dir;
    }
*/
    if (chdir(path)){
        printf("Syntax not supported %s\n", path);
        return 1;
    }
    //ft_strlcpy(cmd->prev_dir, curdir, MAXcurdirLEN);
    //getcwd(curdir, sizeof(curdir));
    //printf("Current dir: %s\n", curdir);
    return (0);
}
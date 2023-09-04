#include "../../include/minishell.h"

int     f_cd(t_simple_cmd *cmd)
{
    char    curdir[MAXPATHLEN];
    //char    path[MAXPATHLEN];
    char    *av;

    av = cmd->argv[1];
    
    //current dir might be unreachable
    /*
    if (!getcwd(curdir, sizeof(curdir)))
        *curdir = '\0';
    */
    if (!av)
        av = getenv("HOME");
    if (!ft_strcmp(av, "-"))
    {
        if (cmd->prev_dir[0] == '\0')
        {
            printf("No previous directory.\n");
            return (1);
        }
        av = cmd->prev_dir;
    }
    printf("args:%s\n", av);
    if (chdir(av)){
        printf("Syntax not supported %s\n", av);
        return 1;
    }
    ft_strlcpy(cmd->prev_dir, curdir, MAXPATHLEN);
    getcwd(curdir, sizeof(curdir));
    printf("Current dir: %s\n", curdir);
    return (0);
}
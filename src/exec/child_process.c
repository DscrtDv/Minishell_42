#include "../../include/minishell.h"

char    *get_path(t_data *data, char *cmd_name)
{
    char    **paths;
    char    *full_path;
    char    *bin_path;
    int     i;

    //bin_path = NULL;
    full_path = ft_getenv(data, "PATH");
    if (!full_path)
        return (NULL);
    i = 0;
    paths = ft_split(full_path, ':');
    while (paths[i])
    {
        //printf("path [%d]: %s\n", i, paths[i]);
        if (!ft_strcmp(paths[i], "/usr/bin"))
        {
            bin_path = ft_substr(paths[i], 0, ft_strlen(paths[i]) + 1);
            ft_strlcat(bin_path, "/", ft_strlen(bin_path) + 2);
            ft_strlcat(bin_path, cmd_name, ft_strlen(bin_path) + ft_strlen(cmd_name) + 1);
            ft_free_array(paths);
            return (bin_path);
        }
        i++;
    }
    return (NULL);

}

void    exec_single(t_data *data, char **envp)
{
    t_cmd   *cmd;
    char    *path;
    char    *cmd_name;
    char *env[] = {NULL};
    char    *arg[] = {"wc", "-l", NULL};

    cmd = &(data->commands[0]);
    cmd_name = data->commands[0].cmd_name;
    path = get_path(data, cmd_name);
    //printf("here\n");
    if (!path)
    {
        error_msg("Path is invalid.\n");
        return ;
    }
    execve(path, arg, env);
    perror("Execution failed.\n");
}
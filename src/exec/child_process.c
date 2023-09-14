#include "../../include/minishell.h"

static bool access_check(char *path)
{
    printf("checking: %s\n", path);
    if (access(path, X_OK) == 0)
        return (true);
    return (false);
}

static bool path_check(char *path)
{
    if (path[0] != '/')
        return (false);
    return (true);
}

static bool     is_splitable(char *path)
{
    if (ft_strchr(path, ':'))
        return (true);
    return (false);
}

static  char    *single_path(char *path, char *cmd_name)
{
    printf("In single path\n");
    if (!path_check(path))
        return (NULL);
    ft_strlcat(path, "/", ft_strlen(path) + 2);
    ft_strlcat(path, cmd_name, ft_strlen(path) + ft_strlen(cmd_name) + 1);
    if (!access_check(path))
        return (NULL);
    return (path);
}

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
    if (!is_splitable(full_path))
        return (single_path(full_path, cmd_name));
    i = 0;
    paths = ft_split(full_path, ':');
    if (!paths)
        malloc_protect(data);
    while (paths[i])
    {
        //printf("path [%d]: %s\n", i, paths[i]);
        if (!ft_strcmp(paths[i], "/bin") || !ft_strcmp(paths[i], "/usr/bin"))
        {
            bin_path = ft_substr(paths[i], 0, ft_strlen(paths[i]) + 1);
            if (!bin_path)
                malloc_protect(data);
            ft_strlcat(bin_path, "/", ft_strlen(bin_path) + 2);
            ft_strlcat(bin_path, cmd_name, ft_strlen(bin_path) + ft_strlen(cmd_name) + 1);
            if (access_check(bin_path))
            {
                ft_free_array(paths);
                return (bin_path);
            }
        }
        i++;
    }
    ft_free_array(paths);
    free(bin_path);
    return (NULL);
}

/*
void    exec_single(t_data *data)
{
    (void)data;
    char *path = "/bin/ls";
    char *env[] = {NULL};
    char *arg[] = {"ls", "-l", NULL};
    if (execve(path, arg, env) == -1)
    {
        perror("execve");
        return ;
    }
}
*/

void    exec_single(t_data *data)
{
    t_cmd   *cmd;
    char    *path;
    char    *cmd_name;
    char    *env[] = {NULL};
    //char    *args[] = {"ls", "-l", NULL};
    //char    *temp = "/bin/ls";

    printf("In exec single\n");
    cmd = &(data->commands[0]);
    cmd_name = data->commands[0].name;
    path = get_path(data, cmd_name);
    printf("Path: %s\n", path);
    if (!path)
        path = cmd_name;
    execve(path, cmd->args, env);
    free_data(data);
    perror("Execution failed.\n");
}

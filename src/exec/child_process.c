#include "../../include/minishell.h"

static bool access_check(char *path)
{
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

static  char    *single_path(char *path, char *name)
{
    if (!path_check(path))
        return (NULL);
    ft_strlcat(path, "/", ft_strlen(path) + 2);
    ft_strlcat(path, name, ft_strlen(path) + ft_strlen(name) + 1);
    if (!access_check(path))
        return (NULL);
    return (path);
}

char    *get_path(t_data *data, char *name)
{
    char    **paths;
    char    *full_path;
    char    *bin_path;
    int     i;

    full_path = ft_getenv(data, "PATH");
    if (!full_path)
        return (NULL);
    if (!is_splitable(full_path))
        return (single_path(full_path, name));
    i = 0;
    paths = ft_split(full_path, ':');
    if (!paths)
        malloc_protect(data);
    while (paths[i])
    {
        if (!ft_strcmp(paths[i], "/bin") || !ft_strcmp(paths[i], "/usr/bin"))
        {
            bin_path = ft_substr(paths[i], 0, ft_strlen(paths[i]) + 1);
            if (!bin_path)
                malloc_protect(data);
            ft_strlcat(bin_path, "/", ft_strlen(bin_path) + 2);
            ft_strlcat(bin_path, name, ft_strlen(bin_path) + ft_strlen(name) + 1);
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

void    exec_single(t_data *data)
{
    t_cmd   *cmd;
    char    *path;
    char    *name;

    exec_redir(data, 0);
    cmd = &(data->commands[0]);
    name = data->commands[0].name;
    path = get_path(data, name);
    if (!path)
        path = name;
    execve(path, cmd->args, NULL);
    free_data(data);
    perror("Execution failed");
}

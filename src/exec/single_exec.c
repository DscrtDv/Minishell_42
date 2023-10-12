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

char *path_join(char *dest, char *src1, char *src2)
{
    char *dest1;
    char *dest2;

    dest1 = ft_strjoin(dest, src1);
    if (!dest1)
        return (NULL);
    dest2 = ft_strjoin(dest1, src2);
    if (!dest2)
        return (free(dest1), NULL);
    return (free(dest1), dest2);
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
            bin_path = path_join(paths[i], "/", name);
            if (!bin_path)
                return (malloc_protect(data), ft_free_array(paths), NULL);
            if (access_check(bin_path))
                return (ft_free_array(paths), bin_path);
            free(bin_path);
        }
        i++;
    }
    ft_free_array(paths);
    return (NULL);
}

int     is_dir(char *file)
{
    struct stat path;
    
    stat(file, &path);
    return S_ISDIR(path.st_mode);
}

void    exec_single(t_data *data)
{
    t_cmd   *cmd;
    char    *path;
    char    *name;

    data->status = 0;
    exec_redir(data, 0);
    cmd = &(data->commands[0]);
    name = data->commands[0].name;
    if (name[0] == '\0')
        exit(data->status);
    if (is_dir(name))
    {
        error_msg(name, "Is a directory", NULL);
        data->status = 126;
        exit(data->status);
    }
    path = get_path(data, name);
    if (!path)
        path = name;
    execve(path, cmd->args, data->envp);
    data->status = set_error(name);
    free_data(data);
    exit(data->status);
}

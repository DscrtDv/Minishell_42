#include "../../include/minishell.h"

void    set_null(t_data *data)
{
    data->n_cmd = 0;
    data->input = NULL;
    data->input_split_by_cmds = NULL;
    data->env = NULL;
    data->envp = NULL;
    data->commands = NULL;
    data->hd_path = NULL;
}

void    perror_call()
{
    perror(RED PROMPT COLOR_RESET);
}

int     is_dir(char *file)
{
    struct stat path;
    
    stat(file, &path);
    return S_ISDIR(path.st_mode);
}

int     set_error(char *name)
{
    int     err;

    err = 0;
    if (errno == 13)
    {
        if (is_dir(name))
            error_msg(name, "Is a directory", NULL);
        else
            error_msg(name, "Permission denied", NULL);
        err = PERM_DENIED;
    }
    else
    {
        if (name[0] == '/' || (name[0] == '.' && name[1] == '/'))
            error_msg(name, "No such file or directory", NULL);
        else
            error_msg(name, "command not found", NULL);
        err = NOT_FOUND;
    }
    return (err);
}

void    error_msg(char *func, char *s1, char *s2)
{
    ft_putstr_fd(RED PROMPT COLOR_RESET ": ", 2);
    ft_putstr_fd(func, 2);
    if (s1)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(s1, 2);
    }
    if (s2)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(s2, 2);
    }
    ft_putchar_fd('\n', 2);
}
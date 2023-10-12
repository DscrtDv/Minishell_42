#include "../../include/minishell.h"

void    set_null(t_data *data)
{
    data->n_cmd = 0;
    data->input = NULL;
    data->input_split_by_cmds = NULL;
    data->env = NULL;
    data->envp = NULL;
    data->commands = NULL;
}

void    perror_call()
{
    perror(RED PROMPT COLOR_RESET);
}

int     set_error(char *name)
{
    int     err;

    err = 0;
    if (errno == 13)
    {
        error_msg(name, "Permission denied", NULL);
        err = 126;
    }
    else
    {
        error_msg(name, "command not found", NULL);
        err = 127;
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
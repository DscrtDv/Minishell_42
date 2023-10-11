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

int     set_error()
{
    if (errno == 13)
        return (126);
    else
        return (127);
}

int    free_data(t_data *data)
{
    /*
        to free
        data:
            - input
            - input_split_by_cmds
            - env
            - commands
            - token list
        cmd:
    */
    if (data->input)
        free(data->input);
    if (data->input_split_by_cmds)
        ft_free_array(data->input_split_by_cmds);
    if (data->env)
        free_list(data->env);
    /*
    if (data->envp)
        ft_free_array(data->envp);
    */
    if (data->commands)
        free_cmds(data);
    set_null(data);
    free(data);
    return (EXIT_SUCCESS);
}

void    error_msg(char *str)
{
    ft_putstr_fd(RED PROMPT COLOR_RESET ": ", 2);
    ft_putstr_fd(str, 2);
}

void    malloc_protect(t_data *data)
{
    free_data(data);
    error_msg("MEM ERR\n");
    exit(137);
}
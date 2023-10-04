
#include "../../include/minishell.h"

t_builtin is_builtin(char *name)
{
    if (!ft_strcmp(name, "echo"))
        return (f_echo);
    if (!ft_strcmp(name, "pwd"))
        return (f_pwd);        
    if (!ft_strcmp(name, "cd"))
        return (f_cd);
    if (!ft_strcmp(name, "env"))
        return (f_env);
    if (!ft_strcmp(name, "export"))
        return (f_export);
    if (!ft_strcmp(name, "unset"))
        return (f_unset);
    if (!ft_strcmp(name, "exit"))
        return (f_exit);
    return (NULL);
}

int     exec_builtin(t_data *data, int index, t_builtin f_builtin)
{
    if (redir_check(data->commands + index))
        redir_type(data, index);
    return (f_builtin(data, index));
}

int     exec_bin(t_data *data)
{
    int     exit_status;

    data->pid = fork();
    if (data->pid < 0)
        return (error_msg("fork failed\n"), 1);
    if (data->pid == 0)
        exec_single(data);
    waitpid(data->pid, &exit_status, 0);
    if (WIFEXITED(exit_status))
        return (WEXITSTATUS(exit_status));
    return (EXIT_FAILURE);
}

static int  exec_multiple(t_data *data)
{
    int     exit_status;
    int     status;

    status = 0;
    data->pid = init_pipes(data, -1, 0);
    if (data->pid == -1)
        return (error_msg("fork err"), -1);
    waitpid(data->pid, &exit_status, 0);
    while (wait(NULL) != -1)
		;
    if (WIFEXITED(exit_status))
        status = WEXITSTATUS(exit_status);
    return (status);
}

static int  exec_simple(t_data *data)
{
    t_builtin   f_builtin;
    
    f_builtin = is_builtin(data->commands[0].name);
    if (f_builtin)
        return (exec_builtin(data, 0, f_builtin));
    else
        return (exec_bin(data));
    return (1);
}

int init_exec(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_cmd)
    {
        data->commands[i].fd_in = STDIN_FILENO;
        data->commands[i].fd_out = STDOUT_FILENO;
        i++;
    }
    //printf("ncmd: %i\n", data->n_cmd);
    if (data->n_cmd == 1)
        return (exec_simple(data));
    else
        return (exec_multiple(data));
    return (1);
}
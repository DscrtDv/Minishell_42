#include "../../include/minishell.h"

//if There is a next command close read
//fd_out = write
//if no next fd_out = std_out
//redir

void    multi_execve(t_data *data, int index)
{
    char    *path;
    t_cmd   cmd;
    
    cmd = data->commands[index];
    path = get_path(data, cmd.name);
    if (!path)
        path = cmd.name;
    execve(path, cmd.args, data->envp);
    perror("Execution failed");
    // FREE
    //free_data(data);
}

int     builtin_child(t_builtin f_builtin, t_data *data, int index)
{
    return (f_builtin(data, index));
}

int     multi_child(t_data *data, int index)
{
    t_cmd   cmd;
    t_builtin f_builtin;
    
    cmd = data->commands[index];
    f_builtin = is_builtin(cmd.name);
    if (!cmd.name)
        exit(EXIT_SUCCESS);
    if (!f_builtin)
        multi_execve(data, index);
    else
        data->status = builtin_child(f_builtin, data, index);
    exit(data->status);
}

void   exec_child(t_data *data, int fd_in, int index)
{
    if ((index + 1) != data->n_cmd)
        close(data->pipe_fd[READ]);
    if (fd_in != -1)
        data->commands[index].fd_in = fd_in;
    data->commands[index].fd_out = data->pipe_fd[WRITE];
    if ((index + 1) == data->n_cmd)
        data->commands[index].fd_out = STDOUT_FILENO;
    if (redir_check(data->commands + index))
        set_fds(data, index);
    if (redir_in(data, index) == -1)
    {
        printf("err redir in\n");
        exit(data->status);
    }
    if (!is_builtin(data->commands[index].name))
    {   
        if (redir_out(data, index) == -1)
        {
            printf("err redir out\n");
            exit(data->status);
        }
    }
    multi_child(data, index);
}

static void     close_pipe(int *fd)
{
    close(fd[WRITE]);
    close(fd[READ]);
}

static int parent_fds(t_data *data, int prev_fd, int index)
{
    if ((index + 1) < data->n_cmd)
        if (close(data->pipe_fd[WRITE]) == -1)
            return (EXIT_FAILURE);
    if (prev_fd != -1)
        if (close(prev_fd) == -1)
            return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int   init_pipes(t_data *data, int prev_fd, int index)
{
    pid_t   pid;

    if ((index + 1) < data->n_cmd)
        if (pipe(data->pipe_fd) == -1)
            return (error_msg("Broken pipe", NULL, NULL), EXIT_FAILURE);
    pid = fork();
    if (pid == -1)
        return (close_pipe(data->pipe_fd), error_msg("fork", NULL, NULL), EXIT_FAILURE);
    if (pid == 0)
    {
        exec_child(data, prev_fd, index);
    }
    if (parent_fds(data, prev_fd, index))
        return (EXIT_FAILURE);
    if ((index + 1) == data->n_cmd)
        return (pid);
    return (init_pipes(data, data->pipe_fd[READ], index + 1));
}
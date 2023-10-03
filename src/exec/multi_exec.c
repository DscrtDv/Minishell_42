#include "../../include/minishell.h"

//if There is a next command close read
//fd_out = write
//if no next fd_out = std_out
//redir

void    multi_execve(t_data *data, int index)
{
    char    *path;
    t_cmd   cmd;
    
    printf("bin\n");
    cmd = data->commands[index];
    path = get_path(data, cmd.name);
    if (!path)
        path = cmd.name;
    execve(path, cmd.args, NULL);
    perror("Execution failed");
    // FREE
    //free_data(data);
}

int     multi_child(t_data *data, int index)
{
    t_cmd   cmd;
    t_builtin f_builtin;
    
    cmd = data->commands[index];
    f_builtin = is_builtin(cmd.name);
    printf("Index: %i | Cmd: %s\n", index, data->commands[index].name);
    //printf("in multichild for %s\n", cmd.name);
    if (!cmd.name)
        exit(EXIT_SUCCESS);
    if (!f_builtin)
        multi_execve(data, index);
    else
    {
        printf("Builtin\n");
        data->status = exec_builtin(data, index, f_builtin);
    }
    exit(data->status);
}

void   exec_child(t_data *data, int fd_in, int index)
{
    //printf("Index: %i | Cmd: %s\n", index, data->commands[index].name);
    if ((index + 1) < data->n_cmd)
        close(data->pipe_fd[READ]);
    if (fd_in != -1)
        data->commands[index].fd_in = fd_in;
    data->commands[index].fd_out = data->pipe_fd[WRITE];
    if ((index + 1) == data->n_cmd)
        data->commands[index].fd_out = STDOUT_FILENO;
    if (redir_check(data->commands + index))
        set_fds(data, index);
    //printf("0\n");
    if (redir_in(data, index))
        exit(data->status);
    //printf("1\n");
    if (redir_out(data, index))
        exit(data->status);
    //printf("2\n");
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
            return (error_msg("pipes\n"), EXIT_FAILURE);
    pid = fork();
    if (pid == -1)
        return (close_pipe(data->pipe_fd), error_msg("fork\n"), EXIT_FAILURE);
    if (pid == 0)
    {
        printf("Child: %s\n", data->commands[index].name);
        exec_child(data, prev_fd, index);
    }
    if (parent_fds(data, prev_fd, index))
        return (error_msg("pipes\n"), EXIT_FAILURE);
    if ((index + 1) == data->n_cmd)
        return (pid);
    //printf("Index: %i | Cmd: %s\n", index, data->commands[index].name);
    return (init_pipes(data, data->pipe_fd[READ], ++index));
}
#include "../../include/minishell.h"

void    close_pipe(int *fd)
{
    close(fd[READ]);
    close(fd[WRITE]);
}

void f_exec(t_data *data, t_cmd cmd)
{
    char *path;
    char *name;

    name = cmd.name;
    path = get_path(data, name);
    if (!path)
        path = name;
    printf("4: exec..\n");
    execve(path, cmd.args, NULL);
    free_data(data);
    perror("Exec failed");
}

int     exec_child(t_data *data, int index)
{
    t_cmd cmd;
    printf("3: exec_child\n");
    cmd = data->commands[index];
    if (!cmd.name)
        exit(EXIT_SUCCESS);
    f_exec(data, cmd);
    return (EXIT_SUCCESS);
}

int     multi_exec(t_data *data, int fd_in, int index)
{
    printf("2: multi_exec\n");
    if (index < data->n_cmd - 1)
        close(data->pipe_fd[READ]);
    if (fd_in != -1)
        data->commands[index].fd_in = STDIN_FILENO;
    data->commands[index].fd_out = data->pipe_fd[WRITE];
    if (index == data->n_cmd - 1)
        data->commands[index].fd_out = STDOUT_FILENO;
    if (redir_check(data->commands + index))        
        exec_redir(data, index);
    if (!redir_in(data, index))
        exit(-1);
    if (!redir_out(data, index))
        exit(-1);
    return (exec_child(data, index));
}

int     handle_parent_fd(t_data *data, int fd_in, int index)
{
    if (index < data->n_cmd - 1)
    {
        if (close(data->pipe_fd[WRITE]) == -1)
            return (error_msg("Close fd failed"), EXIT_FAILURE);
    }
    if (fd_in != -1)
    {
        if (close(fd_in) == -1)
            return (error_msg("Close fd failed"), EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}


int     pipe_engine(t_data *data, int prev_fd, int index)
{
    pid_t   pid;

    printf("1: pipe engine \n");
    if (index < data->n_cmd - 1)
        if (pipe(data->pipe_fd) == -1)
            return (error_msg("pipe"), -1);
    pid = fork();
    if (pid == -1)
        return (close_pipe(data->pipe_fd), -1);
    if (pid == 0)
        multi_exec(data, prev_fd, index);
    //in parent, close write of current and read of previous
    if (handle_parent_fd(data, prev_fd, index) == -1)
        return (EXIT_FAILURE);
    if (index == data->n_cmd)
        return (pid);
    return (pipe_engine(data, data->pipe_fd[READ], index++));
}

int exec_multiple(t_data *data)
{
    int exit_status;
    int status;

    printf("0: exec_multiple\n");
    status = 0;
    data->pid = pipe_engine(data, -1, 0);
    if (data->pid == -1)
        return (1);
    waitpid(data->pid, &exit_status, 0);
    while (wait(NULL) != -1)
        ;
    if (WIFEXITED(exit_status))
        status = WEXITSTATUS(exit_status);
    return (status);
}
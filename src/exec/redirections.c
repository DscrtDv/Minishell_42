#include "../../include/minishell.h"

bool    redir_check(t_cmd *cmd)
{
    if (cmd->n_redir >= 1 && cmd->redir_files && cmd->redirections)
        return (true);
    return (false);
}

int     f_dup(t_data *data, int fd, int fileno)
{
    if (fd == fileno)
        return (0);
    if (dup2(fd, fileno) == -1)
    {
        error_msg("");
        data->status = 1;
        close(fd);
        return (-1);
    }
    close (fd);
    return (EXIT_SUCCESS);
}

int     redir_in(t_data *data, int index)
{
    return (f_dup(data, data->commands[index].fd_in, STDIN_FILENO));
}

int     redir_out(t_data *data, int index)
{
    return (f_dup(data, data->commands[index].fd_out, STDOUT_FILENO));
}

int     check_permissions(t_cmd *cmd, t_redir_type redir, int index)
{
    if (redir == IN_SINGLE || redir == IN_DOUBLE)
    {
        cmd->fd_in = open(cmd->redir_files[index], O_RDONLY);
        if (!cmd->fd_in)
            return (EXIT_FAILURE);
    }
    if (redir == OUT_SINGLE)
    {
        cmd->fd_out = open(cmd->redir_files[index], O_WRONLY | O_CREAT | O_TRUNC, \
        0644);
        if (!cmd->fd_out)
            return (EXIT_FAILURE);
    }
    if (redir == OUT_DOUBLE)
    {
        cmd->fd_out = open(cmd->redir_files[index], O_WRONLY | O_CREAT | O_APPEND, \
        0644);
        if (!cmd->fd_out)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int     redir_type(t_data *data, int index)
{
    t_cmd *cmd;
    int i;

    i = 0;
    cmd = data->commands + index;
    while (cmd->redir_files && cmd->redir_files[i])
    {
        if (check_permissions(cmd, cmd->redirections[i], i) == EXIT_FAILURE)
        {
            error_msg(cmd->redir_files[i]);
            return (EXIT_FAILURE);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int     set_fds(t_data *data, int index)
{
    if (redir_type(data, index))
    {
        data->status = 1;
        exit(data->status);
    }
    return (EXIT_SUCCESS);
}

void    exec_redir(t_data *data, int index)
{
    t_cmd *cmd;

    cmd = data->commands + index;
    if (redir_check(cmd))
        set_fds(data, index);
    else
        return;   
    if (redir_in(data, index) == -1)
        exit(data->status);
    if (redir_out(data, index) == -1)
        exit(data->status);
}
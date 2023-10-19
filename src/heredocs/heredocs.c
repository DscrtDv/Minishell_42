#include "../../include/minishell.h"

static char     *get_delim(char *filename)
{
    size_t i;
    char    *delim;

    i = 0;
    while (filename[i] && filename[i] != '_')
        i++;
    delim = malloc(sizeof(char) * i + 1);
    if (!delim)
        return (NULL);
    ft_strlcpy(delim, filename, i + 1);
    return (delim);
}

static int      create_filename(t_cmd *cmd, int n_hd, int index)
{
    char *fn;
    char *num;
    char *temp;

    num = ft_itoa(n_hd);
    if (!num)
        return (-1);
    temp = ft_strjoin("_", num);
    if (!temp)
        return (free(num), -1);
    fn = ft_strjoin(cmd->redir_files[index], temp);
    if (!fn)
        return (free(num), free(temp), -1);
    free(cmd->redir_files[index]);
    cmd->redir_files[index] = ft_strdup(fn);
    if (!cmd->redir_files[index])
        return (free(num), free(temp), free(fn), -1);
    return (free(num), free(temp), free(fn), 0);
}

int32_t     get_input(t_data *data, char *delim, int fd)
{
    char            *nl;
    int32_t status = 0;
    (void)data;

    while (true)
    {
        nl = readline("heredoc> ");
        if (nl == NULL)
            exit(EXIT_FAILURE);
        if (*nl == '\0')
            ft_putchar_fd('\n', fd);
        else if (ft_strncmp(nl, delim, ft_strlen(delim)) == 0)
            return (free(nl), status);
        else 
        {
            ft_putstr_fd(nl, fd);
            ft_putchar_fd('\n', fd);
        }
        free(nl);
    }
}

static int32_t    hd_write(t_data *data, int index, int hd_index)
{
    int32_t status;
    int fd;
    char *delimiter;

    delimiter = get_delim(data->commands[index].redir_files[hd_index]);
    if (!delimiter)
        return (EXIT_FAILURE);
    fd = open(data->commands[index].redir_files[hd_index], O_WRONLY | O_CREAT | O_APPEND, 
        0644);
    if (!fd)
        return (free(delimiter), EXIT_FAILURE);
    status = get_input(data, delimiter, fd);
    close(fd);
    free(delimiter);
    exit(status);
}

static int      fork_hd(t_data *data, int index, int hd_index)
{
    int32_t     status;
    pid_t       pid;

    status = 0;
    pid = fork();
    if (pid == -1)
        status = 1;
    else if (pid == 0)
        hd_write(data, index, hd_index);
    else
    {
        if (waitpid(pid, &status, 0) == -1)
            status = 1;
        else
            status = WIFEXITED(status);
    }
    return (status);
}

static int32_t     create_heredoc(t_data *data, int index)
{
    t_cmd   *cmd;
    int32_t status;
    int     i;

    i = 0;
    cmd = data->commands + index;

    while (i < cmd->n_redir)
    {
        if (cmd->redirections[i] == IN_DOUBLE)
        {
            if (create_filename(cmd, data->n_hd++, i) == -1)
                malloc_protect(data);
            status = fork_hd(data, index, i);
        }
        i++;
    }
    return (status);
}

int     handle_hd(t_data *data)
{
    int         i;

    i = 0;
    while (i < data->n_cmd)
    {
        if (data->commands[i].has_hd == true)
            data->status = create_heredoc(data, i);
        i++;
    }
    return (data->status);
}

static void     rm_hds(t_data *data, int index)
{
    t_cmd *cmd;
    char *path;
    int     i;

    i = 0;
    cmd = data->commands + index;
    while (i < cmd->n_redir)
    {
        if (cmd->redirections[i] == IN_DOUBLE)
        {
            path = path_join(data->hd_path, "/", cmd->redir_files[i]);
            if (!path)
                malloc_protect(data);
            if (unlink(path) == -1)
                perror("unlink: ");
            free(path);
        }
        i++;
    }
}

void    clean_hds(t_data *data)
{
    int     i;

    i = 0;
    while (i < data->n_cmd)
    {
        if (data->commands[i].has_hd == true)
            rm_hds(data, i);
        i++;
    }
}
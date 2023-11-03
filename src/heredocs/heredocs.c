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
    int  fd;

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
    fd = open(cmd->redir_files[index], O_WRONLY | O_CREAT | O_APPEND, 
        0644);
    if (!fd)
        return (-1);
    return (free(num), free(temp), free(fn), STATUS_OK);
}

int32_t     get_input(t_data *data, char **delims, int fd)
{
    char            *nl;
    char            *exp_nl;
    int i;
    int32_t status; 
    
    status = 0;
    i = 0;
    while (true)
    {
        nl = readline("heredoc> ");
        if (nl == NULL)
            exit(MEM_ERR);
        if (*nl == '\0')
            ft_putchar_fd('\n', fd);
        else if (ft_strncmp(nl, delims[i], ft_strlen(delims[i])) == 0)
        {
            i++;
            free(nl);
            if (!delims[i])
                return (status);
            continue ;
        }
        else 
        {
            exp_nl = expand_heredoc_line(nl, data);
            if (!exp_nl)
                exit(MEM_ERR);
            ft_putstr_fd(exp_nl, fd);
            ft_putchar_fd('\n', fd);
            free(exp_nl);
        }
        free(nl);
    }
    return (status);
}

static int32_t    hd_write(t_cmd *cmd, int hd_index, char **delims)
{
    int32_t status;
    int fd;

    fd = open(cmd->redir_files[hd_index], O_WRONLY | O_CREAT | O_APPEND, 
        0644);
    if (!fd)
        return (EXIT_FAILURE);
    status = get_input(cmd->data, delims, fd);
    close(fd);
    exit(status);
}

static int      fork_hd(t_cmd *cmd, int hd_index, char **delims)
{
    int32_t     status;
    pid_t       pid;

    status = 0;
    pid = fork();
    if (pid == -1)
        status = 1;
    else if (pid == 0)
        hd_write(cmd, hd_index, delims);
    else
    {
        ft_free_array(delims);
        if (waitpid(pid, &status, 0) == -1)
            status = 1;
        else
            status = WIFEXITED(status);
    }
    return (status);
}

static int         set_delims(t_cmd *cmd, int size)
{
    char **delims;
    int j;
    int i;

    delims = malloc(sizeof(char *) * (size + 1));
    if (!delims)
        return (MEM_ERR);
    i = 0;
    j = 0;
    while (i < cmd->n_redir)
    {
        if (cmd->redirections[i] == IN_DOUBLE)
        {
            delims[j] = get_delim(cmd->redir_files[j]);
            if (!delims[j])
                return (ft_free_array(delims), MEM_ERR);
            j++;
        }
        i++;
    }
    delims[j] = NULL;
    return (fork_hd(cmd, (size-1), delims));
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
            if (create_filename(cmd, data->n_hd++, i) != STATUS_OK)
                 malloc_protect(data);
        }
        i++;
    }
    status = set_delims(cmd, data->n_hd);
    return (status);
}

int     handle_hd(t_data *data)
{
    int         i;

    i = 0;
    while (i < data->n_cmd)
    {
        if (data->commands[i].has_hd == true)
        {
            data->status = create_heredoc(data, i);
            if (data->status == MEM_ERR)
                malloc_protect(data);
        }
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
    free(data->hd_path);
	data->hd_path = NULL;
}
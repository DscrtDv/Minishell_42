#include "../../include/minishell.h"

static int     has_heredocs(t_cmd *cmd)
{
    if (cmd->here_doc_delim)
        return (true);
    return (false);
}

static char     *create_filename(t_cmd *cmd, int index)
{
    char *fn;
    char *num;
    char *temp;

    num = ft_itoa(index);
    if (!num)
        return (NULL);
    temp = ft_strjoin("_", num);
    if (!temp)
        return (free(num), NULL);
    fn = ft_strjoin(cmd->here_doc_delim, temp);
    if (!fn)
        return (free(num), free(temp), NULL);
    return (free(num), free(temp), fn);
}

static void     create_heredoc(t_data *data, int index)
{
    char *filename;
    t_cmd *cmd;

    cmd = data->commands + index;
    filename = create_filename(cmd, index);
    if (!filename)
        malloc_protect(data);
    printf("Filename ready: %s\n",filename);
}

int     handle_hd(t_data *data)
{
    t_cmd       **cmds;
    int         i;

    i = 0;
    cmds = &(data->commands);
    while (cmds[i])
    {
        if (has_heredocs(cmds[i]))
            create_heredoc(data, i);
        i++;
    }
    return (0);
}
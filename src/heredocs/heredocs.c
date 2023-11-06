#include "../../include/minishell.h"

int	fork_hd(t_cmd *cmd, int hd_index, char **delims)
{
	int32_t	status;
	pid_t	pid;
	t_data	*data;

	data = cmd->data;
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
			data->status = 1;
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
	}
	return (data->status);
}

static int32_t	create_heredoc(t_data *data, int index)
{
	t_cmd	*cmd;
	int32_t	status;
	int		i;

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

int	handle_hd(t_data *data)
{
	int	i;

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

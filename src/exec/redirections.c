#include "../../include/minishell.h"

int	check_permissions(t_cmd *cmd, t_redir_type redir, int index)
{
	if (redir == IN_SINGLE || redir == IN_DOUBLE)
	{
		cmd->fd_in = open(cmd->redir_files[index], O_RDONLY);
		if (cmd->fd_in == -1)
			return (error_msg(cmd->redir_files[index], err_redir(), NULL) \
			, EXIT_FAILURE);
	}
	if (redir == OUT_SINGLE)
	{
		cmd->fd_out = open(cmd->redir_files[index], \
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
			return (error_msg(cmd->redir_files[index], err_redir(), NULL) \
			, EXIT_FAILURE);
	}
	if (redir == OUT_DOUBLE)
	{
		cmd->fd_out = open(cmd->redir_files[index], \
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fd_out == -1)
			return (error_msg(cmd->redir_files[index], err_redir(), NULL) \
			, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	redir_type(t_data *data, int index)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = data->commands + index;
	while (cmd->redir_files && cmd->redir_files[i])
	{
		if (check_permissions(cmd, cmd->redirections[i], i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	set_fds(t_data *data, int index)
{
	if (redir_type(data, index) == EXIT_FAILURE)
	{
		data->status = 1;
		exit(data->status);
	}
	return (EXIT_SUCCESS);
}

void	exec_redir(t_data *data, int index)
{
	t_cmd	*cmd;

	cmd = data->commands + index;
	if (redir_check(cmd))
		set_fds(data, index);
	else
		return ;
	if (redir_in(data, index) == -1)
		exit(data->status);
	if (redir_out(data, index) == -1)
		exit(data->status);
}

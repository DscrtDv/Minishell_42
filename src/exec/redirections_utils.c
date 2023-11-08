#include "../../include/minishell.h"

int	f_dup(t_data *data, int fd, int fileno)
{
	if (fd == fileno)
		return (0);
	if (dup2(fd, fileno) == -1)
	{
		error_msg("", NULL, NULL);
		data->status = 1;
		close(fd);
		return (-1);
	}
	close (fd);
	return (EXIT_SUCCESS);
}

bool	redir_check(t_cmd *cmd)
{
	if (cmd->n_redir >= 1 && cmd->redir_files && cmd->redirections)
		return (true);
	return (false);
}

int	redir_in(t_data *data, int index)
{
	return (f_dup(data, data->commands[index].fd_in, STDIN_FILENO));
}

int	redir_out(t_data *data, int index)
{
	return (f_dup(data, data->commands[index].fd_out, STDOUT_FILENO));
}

char	*err_redir(void)
{
	if (errno == 2)
		return ("No such file or directory");
	return ("Permission denied");
}

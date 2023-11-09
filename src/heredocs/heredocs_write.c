/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs_write.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:02:48 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 14:02:50 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	input_write(t_data *data, int fd, char *nl)
{
	char	*exp_nl;

	exp_nl = expand_heredoc_line(nl, data);
	if (!exp_nl)
		return (MEM_ERR);
	ft_putstr_fd(exp_nl, fd);
	ft_putchar_fd('\n', fd);
	return (free(exp_nl), STATUS_OK);
}

static int32_t	get_input(t_data *data, char **delims, int fd)
{
	char	*nl;
	int		i;

	i = 0;
	while (true)
	{
		nl = readline("heredoc> ");
		if (nl == NULL)
			return (MEM_ERR);
		if (*nl == '\0')
			ft_putchar_fd('\n', fd);
		else if (ft_strncmp(nl, delims[i], ft_strlen(delims[i])) == 0)
		{
			i++;
			free(nl);
			if (!delims[i])
				return (STATUS_OK);
			continue ;
		}
		else
			if (input_write(data, fd, nl) == MEM_ERR)
				return (free(nl), MEM_ERR);
		free(nl);
	}
	return (STATUS_OK);
}

int32_t	hd_write(t_cmd *cmd, int hd_index, char **delims)
{
	int		fd;
	t_data	*data;

	data = cmd->data;
	fd = open(cmd->redir_files[hd_index], O_WRONLY | O_CREAT | O_TRUNC, \
		0644);
	if (!fd)
		return (EXIT_FAILURE);
	data->status = get_input(data, delims, fd);
	close(fd);
	free_data(data);
	_free_array(delims);
	exit(data->status);
}

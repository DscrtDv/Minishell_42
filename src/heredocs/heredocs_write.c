/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs_write.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:02:48 by tim           #+#    #+#                 */
/*   Updated: 2023/11/10 16:22:42 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	insert_nl(char **hd)
{
	char	*temp;

	if (*hd == NULL)
		*hd = ft_strdup("\n");
	else
	{
		temp = *hd;
		*hd = ft_strjoin(*hd, "\n");
		free(temp);
	}
	if (*hd == NULL)
		return (MEM_ERR);
	return (STATUS_OK);
}

static int	input_write(t_data *data, char **hd, char *nl)
{
	char	*exp_nl;
	char	*temp;

	exp_nl = expand_heredoc_line(nl, data);
	if (!exp_nl)
		return (MEM_ERR);
	if (*hd == NULL)
		*hd = ft_strdup(exp_nl);
	else
	{
		temp = *hd;
		*hd = ft_strjoin(*hd, exp_nl);
		free(temp);
	}
	if (*hd == NULL)
		return (free(exp_nl), MEM_ERR);
	return (free(exp_nl), insert_nl(hd));
}

static int	check_eof(char **delims, int i)
{
	if (!delims[i])
		return (STATUS_OK);
	return (STATUS_KO);
}

static int32_t	get_input(t_data *data, char **delims, char **hd)
{
	char	*nl;
	int		i;

	i = 0;
	while (true)
	{
		nl = readline("heredoc> ");
		if (nl == NULL)
			return (STATUS_OK);
		if (*nl == '\0' || *nl == '\n')
		{
			if (insert_nl(hd) == MEM_ERR)
				return (free(nl), MEM_ERR);
		}
		else if (ft_strncmp(nl, delims[i], ft_strlen(delims[i])) == 0)
		{
			if (check_eof(delims, ++i) == STATUS_OK)
				return (free(nl), STATUS_OK);
		}
		else
			if (input_write(data, hd, nl) == MEM_ERR)
				return (free(nl), MEM_ERR);
		free(nl);
	}
	return (STATUS_OK);
}

int32_t	hd_write(t_cmd *cmd, int hd_index, char **delims)
{
	int		fd;
	t_data	*data;
	char	*hd;

	init_signals(HEREDOC);
	hd = NULL;
	data = cmd->data;
	data->status = get_input(data, delims, &hd);
	fd = open(cmd->redir_files[hd_index], O_WRONLY | O_CREAT | O_TRUNC, \
		0644);
	if (!fd)
		data->status = STATUS_KO;
	if (hd != NULL)
	{
		if (write(fd, hd, ft_strlen(hd)) == -1)
			data->status = STATUS_KO;
	}
	close(fd);
	open_fds(cmd, hd_index);
	free_hd(hd);
	free_data(data, false);
	_free_array(delims);
	exit(data->status);
}

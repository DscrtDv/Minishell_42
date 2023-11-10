/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs_write.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:02:48 by tim           #+#    #+#                 */
/*   Updated: 2023/11/09 19:32:13 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	insert_nl(char **hd)
{
	if (*hd == NULL)
		*hd = ft_strdup("\n");
	else
		*hd = ft_strjoin(*hd, "\n");
	if (*hd == NULL)
		return (MEM_ERR);
	return (STATUS_OK);
}

static int	input_write(t_data *data, char **hd, char *nl)
{
	char	*exp_nl;

	exp_nl = expand_heredoc_line(nl, data);
	if (!exp_nl)
		return (MEM_ERR);
	if (*hd == NULL)
		*hd = ft_strdup(exp_nl);
	else
		*hd = ft_strjoin(*hd, exp_nl);
	if (*hd == NULL)
		return (free(exp_nl), MEM_ERR);
	return (free(exp_nl), insert_nl(hd));
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
				return (MEM_ERR);
		}
		else if (ft_strncmp(nl, delims[i], ft_strlen(delims[i])) == 0)
		{
			i++;
			free(nl);
			if (!delims[i])
				return (STATUS_OK);
			continue ;
		}
		else
			if (input_write(data, hd, nl) == MEM_ERR)
				return (free(nl), MEM_ERR);
		free(nl);
	}
	return (STATUS_OK);
}

static int	open_fds(t_cmd *cmd, int hd_index)
{
	int	i;
	int	fd;

	i = 0;
	while (i < cmd->n_redir)
	{
		if (cmd->redirections[i] == IN_DOUBLE && i != hd_index)
		{
			fd = open(cmd->redir_files[i], O_WRONLY | O_CREAT | O_TRUNC, \
					0644);
			if (!fd)
				return (STATUS_KO);
			close(fd);
		}
		i++;
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
		return (EXIT_FAILURE);
	if (hd != NULL)
	{	
		if (write(fd, hd, ft_strlen(hd)) == -1)
			data->status = STATUS_KO;
	}
	close(fd);
	open_fds(cmd, hd_index);
	free(hd);
	free_data(data);
	_free_array(delims);
	exit(data->status);
}

// static int	input_write(t_data *data, int fd, char *nl)
// {
// 	char	*exp_nl;

// 	exp_nl = expand_heredoc_line(nl, data);
// 	if (!exp_nl)
// 		return (MEM_ERR);
// 	ft_putstr_fd(exp_nl, fd);
// 	ft_putchar_fd('\n', fd);
// 	return (free(exp_nl), STATUS_OK);
// }

// static int32_t	get_input(t_data *data, char **delims, int fd)
// {
// 	char	*nl;
// 	int		i;

// 	i = 0;
// 	while (true)
// 	{
// 		nl = readline("heredoc> ");
// 		if (nl == NULL)
// 			return (MEM_ERR);
// 		if (*nl == '\0')
// 			ft_putchar_fd('\n', fd);
// 		else if (ft_strncmp(nl, delims[i], ft_strlen(delims[i])) == 0)
// 		{
// 			i++;
// 			free(nl);
// 			if (!delims[i])
// 				return (STATUS_OK);
// 			continue ;
// 		}
// 		else
// 			if (input_write(data, fd, nl) == MEM_ERR)
// 				return (free(nl), MEM_ERR);
// 		free(nl);
// 	}
// 	return (STATUS_OK);
// }
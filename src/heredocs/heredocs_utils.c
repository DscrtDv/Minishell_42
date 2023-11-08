/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:02:34 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 14:02:35 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_delim(char *filename)
{
	size_t	i;
	char	*delim;

	i = 0;
	while (filename[i] && filename[i] != '_')
		i++;
	delim = malloc(sizeof(char) * i + 1);
	if (!delim)
		return (NULL);
	ft_strlcpy(delim, filename, i + 1);
	return (delim);
}

int	set_delims(t_cmd *cmd, int size)
{
	char	**delims;
	int		j;
	int		i;

	delims = malloc(sizeof(char *) * (size + 1));
	if (!delims)
		return (MEM_ERR);
	i = 0;
	j = 0;
	while (i < cmd->n_redir)
	{
		if (cmd->redirections[i] == IN_DOUBLE)
		{
			delims[j] = get_delim(cmd->redir_files[i]);
			if (!delims[j])
				return (ft_free_array(delims), MEM_ERR);
			j++;
		}
		i++;
	}
	delims[j] = NULL;
	return (fork_hd(cmd, (size - 1), delims));
}

int	create_filename(t_cmd *cmd, int n_hd, int index)
{
	char	*fn;
	char	*num;
	char	*temp;
	int		fd;

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
	fd = open(cmd->redir_files[index], O_WRONLY | O_CREAT | O_APPEND, \
		0644);
	if (!fd)
		return (free(num), free(temp), free(fn), -1);
	return (free(num), free(temp), free(fn), STATUS_OK);
}

static void	rm_hds(t_data *data, int index)
{
	t_cmd	*cmd;
	char	*path;
	int		i;

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

void	clean_hds(t_data *data)
{
	int	i;

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

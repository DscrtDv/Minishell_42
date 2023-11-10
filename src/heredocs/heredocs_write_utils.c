/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs_write_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/10 16:12:42 by tcensier      #+#    #+#                 */
/*   Updated: 2023/11/10 16:14:28 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_fds(t_cmd *cmd, int hd_index)
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

void	free_hd(char *hd)
{
	if (hd != NULL)
		free(hd);
	hd = NULL;
}

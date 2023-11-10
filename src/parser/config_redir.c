/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_redir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 10:04:32 by rares         #+#    #+#                 */
/*   Updated: 2023/11/10 17:15:13 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_redirections_out(t_cmd *cmd, t_token *tokens)
{
	while (tokens && tokens != NULL)
	{
		if (ft_strncmp(tokens->str, ">", 1) == 0 && ft_strlen(tokens->str) == 1)
		{
			tokens->type = OUT_SINGLE;
			tokens->next->type = -2;
			cmd->n_redir++;
		}
		else if (ft_strncmp(tokens->str, ">>", 2) == 0
			&& ft_strlen(tokens->str) == 2)
		{
			tokens->type = OUT_DOUBLE;
			tokens->next->type = -2;
			cmd->n_redir++;
		}
		tokens = tokens->next;
	}
}

static void	set_redirections_in(t_cmd *cmd, t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens != NULL)
	{
		if (ft_strncmp(tokens->str, "<", 1) == 0 && ft_strlen(tokens->str) == 1)
		{
			tokens->type = IN_SINGLE;
			tokens->next->type = -2;
			cmd->n_redir++;
		}
		else if (ft_strncmp(tokens->str, "<<", 2) == 0
			&& ft_strlen(tokens->str) == 2)
		{
			tokens->type = IN_DOUBLE;
			tokens->next->type = -2;
			cmd->n_redir++;
			cmd->has_hd = true;
			if (i == 0 && tokens->next->next != NULL)
				tokens->next->next->type = -3;
		}
		tokens = tokens->next;
		i++;
	}
}

void	set_redirections_type(t_cmd *cmd, t_token *tokens)
{
	set_redirections_in(cmd, tokens);
	set_redirections_out(cmd, tokens);
}

t_cmd	*configure_redirections(t_cmd *cmd, t_token *tokens)
{
	int	i;

	cmd->redirections = malloc(sizeof(t_redir_type) *(cmd->n_redir + 1));
	if (cmd->redirections == NULL)
		return (NULL);
	cmd->redir_files = malloc(sizeof(char *) * (cmd->n_redir + 1));
	if (cmd->redir_files == NULL)
		return (NULL);
	i = 0;
	while (tokens != NULL)
	{
		if (tokens->type == IN_SINGLE || tokens->type == IN_DOUBLE
			|| tokens->type == OUT_SINGLE || tokens->type == OUT_DOUBLE)
		{
			cmd->redir_files[i] = ft_strdup(tokens->next->str);
			cmd->redirections[i] = tokens->type;
			i++;
		}
		tokens = tokens->next;
	}
	cmd->redir_files[i] = NULL;
	return (cmd);
}

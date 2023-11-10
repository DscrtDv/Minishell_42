/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 10:27:44 by rares         #+#    #+#                 */
/*   Updated: 2023/11/10 10:51:18 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*configure_command_data(t_cmd *cmd, t_token *tokens)
{
	int	i;

	cmd->tokens = tokens;
	if (tokens->type == -1)
	{
		cmd->name = ft_strdup(tokens->str);
		if (cmd->name == NULL)
			return (NULL);
	}
	cmd->args = malloc(sizeof(char *) * (cmd->n_args + 1));
	if (cmd->args == NULL)
		return (NULL);
	i = 0;
	while (tokens != NULL)
	{	
		if (tokens->type == -1)
		{
			cmd->args[i] = ft_strdup(tokens->str);
			printf("Arg[%d]: %s\n", i, cmd->args[i]);
			if (cmd->args[i++] == NULL)
				return (NULL);
		}
		tokens = tokens->next;
	}
	cmd->args[i] = NULL;
	return (cmd);
}

static void	init_cmd_data(t_cmd *cmd, t_data *data)
{
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->tokens = NULL;
	cmd->redir_files = NULL;
	cmd->redirections = NULL;
	cmd->n_redir = 0;
	cmd->data = data;
	data->cmd_initialized = true;
}

static int	build_command(t_cmd *cmd, t_data *data, char *command)
{
	t_token	*tokens;

	tokens = NULL;
	init_cmd_data(cmd, data);
	tokens = tokenize(command, 0, tokens);
	if (tokens == NULL)
		return (1);
	cmd->tokens = tokens;
	set_redirections_type(cmd, tokens);
	if (cmd->n_redir != 0)
	{
		if (configure_redirections(cmd, tokens) == NULL)
			return (1);
	}
	if (expander(cmd, data) == 1 || remove_outer_quotes(tokens) == 1
		|| remove_outer_quotes_redir(cmd) == 1)
	{
		cmd->tokens = tokens;
		return (1);
	}
	cmd->n_args = n_args(tokens);
	cmd = configure_command_data(cmd, tokens);
	if (cmd == NULL)
		return (1);
	return (0);
}

int	command_builder(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	cmd = ft_calloc(data->n_cmd, sizeof(t_cmd));
	if (cmd == NULL)
		return (1);
	data->commands = cmd;
	cmd->has_hd = false;
	i = 0;
	while (i < data->n_cmd)
	{
		if (data->n_cmd == 1)
		{
			if (build_command(cmd + i, data, data->input) != 0)
				return (1);
		}
		else
		{
			if (build_command(cmd + i, data, data->input_split_by_cmds[i]) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

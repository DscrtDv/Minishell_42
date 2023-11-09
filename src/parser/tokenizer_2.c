/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 10:10:57 by rares         #+#    #+#                 */
/*   Updated: 2023/11/09 10:11:12 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*isolate_redir(char *command, char c, int *i, char *word)
{
	int	start;

	start = *i;
	if (c == '>')
	{
		(*i)++;
		if (command[*i] != '\0' && command[*i] == '>')
			(*i)++;
	}
	if (c == '<')
	{
		(*i)++;
		if (command[*i] != '\0' && command[*i] == '<')
			(*i)++;
	}
	word = _isolate_token(command, start, *i);
	return (word);
}

t_token	*isolate_redir_no_spaces(char *command, int *i)
{
	char	*word;
	t_token	*new_token;

	word = NULL;
	new_token = NULL;
	word = isolate_token(command, *i);
	if (word == NULL)
		return (NULL);
	new_token = create_token(word);
	if (new_token == NULL)
	{
		printf("Failed to create new_token node\n");
		free (word);
		word = NULL;
		return (NULL);
	}
	return (new_token);
}

static void	check_node_size(t_token **tokens)
{
	if (_lstsize(*tokens) != 0)
	{
		free((*tokens)->str);
		free(*tokens);
		tokens = NULL;
	}
}

t_token	*save_redir(t_token **tokens, char *command, int *i)
{
	char		*word;
	t_token		*new_token;

	word = NULL;
	new_token = NULL;
	word = isolate_redir(command, command[*i], i, word);
	if (word == NULL)
		return (check_node_size(tokens), NULL);
	new_token = create_token(word);
	if (new_token == NULL)
	{
		free(word);
		word = NULL;
		printf("Failed to create new_token node\n");
		return (NULL);
	}
	insert_at_end(tokens, new_token);
	if (command[*i] != ' ')
	{
		new_token = isolate_redir_no_spaces(command, i);
		if (new_token == NULL)
			return (NULL);
		insert_at_end(tokens, new_token);
	}
	return (*tokens);
}

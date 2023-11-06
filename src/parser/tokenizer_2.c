
#include "../../include/minishell.h"

t_token *isolate_redir_no_spaces(char *command, int *i)
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

t_token *save_redir(t_token **tokens, char *command, int *i)
{
	char		*word;
	t_token		*new_token;
	
	word = NULL;
	new_token = NULL;
	word = isolate_redir(command, command[*i], i, word); //maloc protected
	if (word == NULL)
	{
		if (_lstsize(*tokens) != 0)
		{
			free((*tokens)->str);
			free(*tokens);
			tokens = NULL;
		}
		return (NULL);
	}
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
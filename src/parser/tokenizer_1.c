
#include "../../include/minishell.h"

t_token	*save_token(t_token **tokens, char *command, int *i) //malloc protected
{
	char		*word;
	t_token		*new_token;
	
	word = NULL;
	new_token = NULL;
	while (ft_isspace(command[*i]) == 1)
		(*i)++;
	if (command[*i] == '>' || command[*i] == '<')
		return (*tokens);
	// if (command[*i] == '\0')
	// 	break ;
	word = isolate_token(command, *i);
	if (word == NULL)
		return (NULL);
	new_token = create_token(word);
	if (new_token == NULL)
	{
		printf("Failed to create new_token node\n");
		free(word);
		word = NULL;
		return (NULL);
	}
	insert_at_end(tokens, new_token);
	return (*tokens);
}

t_token	*tokenize(char *command)
{
	int			i;
	t_token		*tokens;
	
	i = 0;
	tokens = NULL;
	while (command && command[i])
	{
		if (((i == 0 && (command[i] != '>' && command[i] != '<')) || (command[i] == ' '))
			&& (not_in_quotes(command, i) == true))
		{
			while (ft_isspace(command[i]) == 1)
				i++;
			if (command[i] == '>' || command[i] == '<')
				continue ;
			if (command[i] == '\0')
				break ;
			tokens = save_token(&tokens, command, &i);
			if (tokens == NULL)
				return (NULL);
		}
		else if ((command[i] == '<' || command[i] == '>')
			&& (not_in_quotes(command, i) == true))
		{
			tokens = save_redir(&tokens, command, &i);// malloc protected
			if (tokens == NULL)
				return (NULL);
			continue ;
		}
		i++;
	}
	return (tokens);
}



// static void  tokenize_loop(char *command, t_token **tokens, int *i)
// {
// 	while (command && command[*i])
// 	{
// 		if (((*i == 0 && (command[*i] != '>' && command[*i] != '<')) || (command[*i] == ' '))
// 			&& (not_in_quotes(command, i) == true))
// 		{
// 			while (ft_isspace(command[*i]) == 1)
// 				(*i)++;
// 			if (command[*i] == '>' || command[*i] == '<')
// 				continue ;
// 			if (command[*i] == '\0')
// 				break ;
// 			tokens = save_token(&tokens, command, &i);
// 			if (tokens == NULL)
// 				return (NULL);
// 		}
// 		else if ((command[*i] == '<' || command[*i] == '>')
// 			&& (not_in_quotes(command, *i) == true))
// 		{
// 			tokens = save_redir(&tokens, command, &i);
// 			if (tokens == NULL)
// 				return (NULL);
// 			continue ;

// 		}
// 		(*i)++;
// 	}
// }

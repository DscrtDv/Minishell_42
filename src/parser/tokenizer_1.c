
#include "../../include/minishell.h"

char	*_isolate_token(char *input, int start, int end)
{
	int		len;
	char	*token;
	
	len = end - start;
	token = ft_substr(input, start, len);
	if (token == NULL)
	{
		printf("Error while isolating the redir token\n");
		return (NULL);
	}
	return (token);
}

char	*isolate_token(char *command, int i)
{
	int		end_pos;
	int		len_token;
	char	*token;

	end_pos = get_end_token_index(command, i);
	len_token = end_pos - i;
	token = ft_substr(command, i, len_token);
	if (token == NULL)
	{
		printf ("Error while isolating the token\n");
		return (NULL);
	}
	return (token);
}

t_token	*save_token(t_token **tokens, char *command, int *i)
{
	char		*word;
	t_token		*new_token;
	
	word = NULL;
	new_token = NULL;
	while (ft_isspace(command[*i]) == 1)
		(*i)++;
	if (command[*i] == '>' || command[*i] == '<')
		return (*tokens);
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


#include"../minishell.h"

// t_token	*create_node()
// {
// 	t_token	*new_node;
	
// 	new_node = malloc(sizeof(t_token));
// 	if (new_node == NULL)
// 		raise_error_free("Failed to allocate memmory for the t_token node", s_data);
// 	new_node->next = NULL;
// 	new_node->str = NULL;
// 	new_node->type = 0;
// 	return (new_node);
// }

void	split_by_commands(t_data *data)
{
	int		i;
	int		j;
	char	*input;

	i = 0;
	input = data->input;
	get_cmd_count(data);
	data->input_split_by_cmds = malloc(sizeof(char *) * (data->cmd_count + 1));
	if (data->input_split_by_cmds == NULL)
		raise_error_free("Failed to allocate memory for the input_split_by_cmds", data);
	i = 0;
	j = 0;
	while (input && input[i])
	{
		if ((j == 0 ) && (input[i] == '|' && not_in_quotes(input, i) == 1)) //first valid pipe found
			split_lefmost_cmd(data, input, i, &j);
		if ((input[i] == '|' && not_in_quotes(input, i) == 1)) // valid pipes found
			split_into_cmds(data, input, i, &j);
		i++;
	}
	data->input_split_by_cmds[j] = NULL; // end the command array
}

t_token	*create_token(char *word)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->str = word;
	new_token->type = -1;
	new_token->next = NULL;
	
	return (new_token);
}

t_token	*get_to_last_node(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void insert_at_end(t_token **lst, t_token *new)
{
	t_token	*temp;
	
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = get_to_last_node(*lst);
	temp->next = new;
}


t_token	*save_token(t_token **tokens, char *command, int *i)
{
	char		*word;
	t_token		*new_token;
	
	while (ft_isspace(command[*i]) == 1) //skip whitespace
		(*i)++;
	if (command[*i] == '>' || command[*i] == '<')
		return(*tokens);
	// if (command[*i] == '\0')
	// 	break ;
	word = isolate_token(command, *i);
	new_token = create_token(word);
	if (new_token == NULL)
		raise_error("Failed to create new_token node");//and free
	insert_at_end(tokens, new_token);
	return (*tokens);
}

t_token *save_redir(t_token **tokens, char *command, int *i)
{
	char		*word;
	t_token		*new_token;
	
	word = NULL;
	word = isolate_redir(command, command[*i], i, word);
	new_token = create_token(word);
	if (new_token == NULL)
		raise_error("Failed to create new_token node"); //and free
	insert_at_end(tokens, new_token);
	if (command[*i] != ' ')
	{
		word = isolate_token(command, *i);
		new_token = create_token(word);
		if (new_token == NULL)
			raise_error("Failed to create new_token node"); //and free
		insert_at_end(tokens, new_token);
	}
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
			&& (not_in_quotes(command, i) == 1))
		{
			while (ft_isspace(command[i]) == 1) //skip whitespace
				(i)++;
			if (command[i] == '>' || command[i] == '<')
				continue ;
			if (command[i] == '\0')
				break ;
			tokens = save_token(&tokens, command, &i);
			
		}
		else if ((command[i] == '<' || command[i] == '>')
			&& (not_in_quotes(command, i) == 1))
		{
			tokens = save_redir(&tokens, command, &i);
			continue ;
		}
		i++;
	}
	return(tokens);
}

void	test_print_tokens(t_token *tokens)
{
	while (tokens && tokens != NULL)
	{
		printf("TOKEN= %s\n", tokens->str);
		tokens = tokens->next;
	}
 }

t_cmd	*build_command(t_cmd *cmd, char *command)
{
	t_token	*tokens;
	
	cmd->cmd_name = NULL;
	cmd->cmd_args = NULL;
	cmd->redirections = 0;
	
	tokens = tokenize(command);
	test_print_tokens(tokens);
	if (tokens == NULL)
		return (NULL);
	return (cmd);
}

void command_builder(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd) * data->cmd_count); //allocates memory the cmd structs 
	if (cmd == NULL)
		raise_error_free("Failed to allocate memory for cmd structs", data);
	i = 0;
	while(i < data->cmd_count)
	{
		if (data->cmd_count == 1) //only 1 command
		{
			build_command(cmd + i, data->input);
			//break ;
			// if (build_command(cmd + i, data->input) == NULL)
			// raise_error_free("Failed to build command", data);
		}
		else //multiple commands
		{
			printf("\n---Command %d---\n", i);
			build_command(cmd + i, data->input_split_by_cmds[i]);
			// if (build_command(cmd + i, data->input_split_by_cmds[i]) == NULL)
			// 	raise_error_free("Failed to build command", data);
			
		}
		i++;
	}
}



//---OLD---//

// void	split_by_pipes(t_data *data)
// {
// 	if (ft_strchr(data->input, '|') != 0)
// 	{
// 		data->input_split_by_cmds = ft_split(data->input, '|');
// 		if (data->input_split_by_cmds == NULL)
// 			raise_error_free("Error while splitting by pipes.");
// 	}
// }

// void	split_by_delimiters_verson2(t_data *data)
// {
// 	int		i;
// 	int		end_token_index;
// 	char	*input;
	
// 	i = 0;
// 	input = data->input;
// 	while(input[i])
// 	{
// 		if ((i == 0) || (ft_strchr(" -$\'\"<>", input[i]) != 0)) // delimiter found
// 		{	
// 			while (ft_isspace(input[i]) == 1)
// 				i++;
// 			if (input[i] == '\'')
// 			{
// 				i = skip_quotes(input, i);
// 			}
// 			if (input[i] == '\0')
// 				break;

// 			end_token_index = get_end_token_index(input, i);
// 			isolate_token(input, i, end_token_index);
// 		}
// 		if (input[i] == '|')
// 			data->cmd_count++;
// 		i++;
// 	}
// 	// allocate memory to hold the input split by pipes //
// 	data->input_split_by_cmds = malloc(sizeof(char *) * (data->cmd_count + 10));
// 	if (data->input_split_by_cmds == NULL)
// 		raise_error_free("Error while allocating memory for the input_split_by_cmds");
	
// }

// void	split_by_delimiters_first(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	int		end_token_index;
// 	char	**input;
// 	i = 0;
// 	input = data->input_split_by_cmds;
// 	if (ft_strchr(data->input, '|') != 0)
// 	{
// 		while(input[i])
// 		{	
// 			j = 0;
// 			printf ("\n-----Command %d-----\n", i);
// 			while(input[i][j])
// 			{
// 				if ((j == 0) || (ft_strchr(" -$<>", input[i][j]) != 0)) // delimiter found
// 				{	
// 					while (ft_isspace(input[i][j]) == 1)
// 						j++;
// 					if (input[i][j] == '\0')
// 						break ;
// 					end_token_index = get_end_token_index(input[i], j);
// 					isolate_tokens(input[i], j, end_token_index);
// 				}
// 				j++;
// 			}
// 			i++;
// 		}
// 	}
// }
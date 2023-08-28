
#include"../minishell.h"

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
		if ((j == 0 ) && (input[i] == '|' && not_in_quotes(input, i) == true)) //first valid pipe found
			split_lefmost_cmd(data, input, i, &j);
		if ((input[i] == '|' && not_in_quotes(input, i) == true)) // valid pipes found
			split_into_cmds(data, input, i, &j);
		i++;
	}
	data->input_split_by_cmds[j] = NULL; // end the command array
}

t_token	*save_token(t_token **tokens, char *command, int *i)
{
	char		*word;
	t_token		*new_token;
	
	while (ft_isspace(command[*i]) == 1) //skip whitespace
		(*i)++;
	if (command[*i] == '>' || command[*i] == '<')
		return (*tokens);
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
			&& (not_in_quotes(command, i) == true))
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
			&& (not_in_quotes(command, i) == true))
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

static void	config_redirection_data(t_cmd *cmd, t_token *tokens)
{
	(void)cmd;

	while (tokens && tokens != NULL)
	{
		if (ft_strncmp(tokens->str, ">", 1) == 0 && ft_strlen(tokens->str) == 1)
		{
			tokens->type = OUT_SINGLE;
			printf("(%d) > found\n", tokens->type);
		}
		else if (ft_strncmp(tokens->str, ">>", 2) == 0 && ft_strlen(tokens->str) == 2)
		{
			tokens->type = OUT_DOUBLE;
			printf("(%d) >> found\n", tokens->type);
		}
		else if (ft_strncmp(tokens->str, "<", 1) == 0 && ft_strlen(tokens->str) == 1)
		{
			tokens->type = IN_SINGLE;
			printf("(%d) < found\n", tokens->type);
		}
		else if (ft_strncmp(tokens->str, "<<", 2) == 0 && ft_strlen(tokens->str) == 2)
		{
			tokens->type = IN_DOUBLE;
			printf("(%d) << found\n", tokens->type);
		}
		tokens = tokens->next;

	}
}

char	*cleaned_str(char *str, char c, int index_l, int index_r)
{
	int		j;
	int		x;
	char	*new_str;

	new_str = malloc((sizeof(char) * ft_strlen(str)) + 1 - 2);
	printf("Size of new_str = %zu\n", sizeof(char) * ft_strlen(str) + 1 - 2);
	if (new_str == NULL)
		raise_error("Failed to allocate memory for new_str"); //-> free data + structs!!!
	j = 0;
	x = 0;
	while (str && str[x])
	{
		
		if (x == index_r || x == index_l)
			x++;
		while (str[x] == c)
			x++;
		new_str[j] = str[x];
		j++;
		x++;
	}
	new_str[j] = '\0';
	return (new_str);
}
//-> does not work with "''"'""' expected: ''"" but mine is: ''''
static void	remove_outer_quotes(t_token *tokens)
{
	int		i;
	int		index_l;
	int		index_r;
	char	*str;
	char	*new_str;

	while (tokens && tokens != NULL)
	{
		i = 0;
		str = tokens->str;
		while (str && str[i])
		{
			if (str[i] == '\'')
			{
				index_l = i; //->leftside quote inxex
				i++;
				while (str[i] != '\0' && str[i] != '\'')
					i++;
				index_r = i; //rightside quote index
				printf("S-index_l = %d\nS-index_r = %d\n", index_l, index_r);
				new_str = cleaned_str(str, '\'', index_l, index_r);
				str = new_str;
				free(new_str);
			}
			else if (str[i] == '\"')
			{
				index_l = i; 
				i++;
				while (str[i] != '\0' && str[i] != '\"')
					i++;
				index_r = i;
				printf("D-index_l = %d\nD-index_r = %d\n", index_l, index_r);
				new_str = cleaned_str(str, '\"', index_l, index_r);
				str = new_str;
				free(new_str);
			}
			if (str[i] != '\'' || str[i] != '\"')
				i++;
			else
				i = index_r;
		}
		printf("New str: %s\n", str);
		//free(str);
		tokens = tokens->next;
	}
}

t_cmd	*build_command(t_cmd *cmd, char *command)
{
	t_token	*tokens;
	
	cmd->cmd_name = NULL;
	cmd->cmd_args = NULL;
	cmd->redir_count = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->redir_files = NULL;
	cmd->redirections = 0;
	
	tokens = tokenize(command); // -->per command
	test_print_tokens(tokens);
	config_redirection_data(cmd, tokens);
	remove_outer_quotes(tokens);

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
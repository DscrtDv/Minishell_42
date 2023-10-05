#include"../../include/minishell.h"

int	split_by_commands(t_data *data)
{
	int		i;
	int		j;
	char	*input;

	i = 0;
	input = data->input;
	get_n_cmd(data);
	data->input_split_by_cmds = malloc(sizeof(char *) * (data->n_cmd + 1)); // FREE
	malloc_calls++;
	if (data->input_split_by_cmds == NULL)
	{
		printf("Failed to allocate memory for the input_split_by_cmds\n"); //-->FREE
		return (1);
	}
	i = 0;
	j = 0;
	while (input && input[i])
	{
		if ((j == 0 ) && (input[i] == '|' && not_in_quotes(input, i) == true)) //first valid pipe found
		{
			if (split_lefmost_cmd(data, input, i, &j) == 1)
				return (1);
		}
		if ((input[i] == '|' && not_in_quotes(input, i) == true)) // valid pipes found
			split_into_cmds(data, input, i, &j);
		i++;
	}
	data->input_split_by_cmds[j] = NULL;
	return (0);
}

t_token	*save_token(t_token **tokens, char *command, int *i)
{
	char		*word;
	t_token		*new_token;
	
	while (ft_isspace(command[*i]) == 1)
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
		//free(word);
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
			while (ft_isspace(command[i]) == 1)
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

// static void	test_print_tokens(t_token *tokens)
// {
// 	while (tokens && tokens != NULL)
// 	{
// 		//printf("TOKEN= %s\n", tokens->str);
// 		tokens = tokens->next;
// 	}
// }

int	n_args(t_token *tokens)
{
	int	args_count;

	args_count = 0;
	while (tokens != NULL && tokens->type == -1)
	{
		args_count++;
		tokens = tokens->next;
	}
	return (args_count);
}

static void	set_redirections_type(t_cmd *cmd, t_token *tokens)
{
	while (tokens && tokens != NULL)
	{
		if (ft_strncmp(tokens->str, ">", 1) == 0 && ft_strlen(tokens->str) == 1)
		{
			tokens->type = OUT_SINGLE;
			cmd->n_redir++;
			//printf("(%d) > found\n", tokens->type);
		}
		else if (ft_strncmp(tokens->str, ">>", 2) == 0 && ft_strlen(tokens->str) == 2)
		{
			tokens->type = OUT_DOUBLE;
				cmd->n_redir++;
			//printf("(%d) >> found\n", tokens->type);
		}
		else if (ft_strncmp(tokens->str, "<", 1) == 0 && ft_strlen(tokens->str) == 1)
		{
			tokens->type = IN_SINGLE;
				cmd->n_redir++;
			//printf("(%d) < found\n", tokens->type);
		}
		else if (ft_strncmp(tokens->str, "<<", 2) == 0 && ft_strlen(tokens->str) == 2)
		{
			tokens->type = IN_DOUBLE;
				cmd->n_redir++;
			//printf("(%d) << found\n", tokens->type);
		}
		tokens = tokens->next;
	}
}

static t_cmd *configure_redirections(t_cmd *cmd, t_token *tokens)
{
	int	i;

	cmd->redirections = malloc(sizeof(t_redir_type) *(cmd->n_redir + 1)); //FREE
	malloc_calls++;
	if (cmd->redirections == NULL)
		return (NULL);
	cmd->redir_files = malloc(sizeof(char *) * (cmd->n_redir + 1)); //FREE
	malloc_calls++;
	if (cmd->redir_files == NULL)
		return (NULL);
	i = 0;
	while (tokens != NULL)
	{
		if (tokens->type != -1) //maybe make it more clear that -1 equals WORD
		{
			//cmd->redir_files[i] = tokens->next->str; !!!!!
			cmd->redir_files[i] = ft_strdup(tokens->next->str); // FREE
			malloc_calls++;
			cmd->redirections[i] = tokens->type;
			i++;
		}
		tokens = tokens->next;
	}
	cmd->redir_files[i] = NULL;
	return (cmd);
}

static void	remove_outer_quotes(t_token *tokens)
{
	int		i;
	int		index_l;
	int		index_r;
	char	*str;
	char 	*clean_str;
	char	*new_str;

	while (tokens != NULL)
	{
		i = 0;
		str = tokens->str;
		new_str = "";
		clean_str = NULL;
		while (str && str[i])
		{
			if (str[i] == '\'')
			{
				index_l = i; //->leftside quote index
				i++;
				while (str[i] != '\0' && str[i] != '\'')
					i++;
				index_r = i; //rightside quote index
				clean_str = ft_substr(str, index_l + 1, index_r - index_l - 1);
				new_str = ft_strjoin(new_str, clean_str);
				free(clean_str);
			}
			else if (str[i] == '\"')
			{
				index_l = i;
				i++;
				while (str[i] != '\0' && str[i] != '\"')
					i++;
				index_r = i;
				clean_str = ft_substr(str, index_l + 1, index_r - index_l - 1);
				new_str = ft_strjoin(new_str, clean_str);
				free(clean_str);
			}
			else
			{
				index_l = i;
				while (str[i] && (str[i] != '\'' || str[i] != '\"'))
					i++;
				index_r = i;
				clean_str = ft_substr(str, index_l, index_r - index_l);
				new_str = ft_strjoin(new_str, clean_str);
				free(clean_str);
			}
			if (str[i] != '\'' && str[i] != '\"')
				i++;
			else
				i = index_r + 1;
		}
		if (tokens->str[0] != '\0')
			free(tokens->str);
		tokens->str = ft_strdup(new_str);
		if (new_str[0] != '\0')
			free(new_str);
		tokens = tokens->next;
	}
}

static t_cmd	*configure_command_data(t_cmd *cmd, t_token *tokens)
{
	int	i;

	if (tokens->type == -1)
	{
		cmd->name = ft_strdup(tokens->str);
		malloc_calls++;
	}
	//tokens = tokens->next;
	cmd->args = malloc(sizeof(char *) * (cmd->n_args + 1)); //FREE
	malloc_calls++;
	i = 0;
	//printf("Start of configure_command_data\n");
	while (tokens != NULL && tokens->type == -1)
	{	
		cmd->args[i] = ft_strdup(tokens->str); // FREE
		malloc_calls++;
		i++;
		tokens = tokens->next;
	}
	cmd->args[i] = NULL;
	//printf("End of configure_command_data\n");
	return(cmd);
}

t_cmd	*build_command(t_cmd *cmd, char *command)
{
	t_token	*tokens;
	
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->n_redir = 0;
	cmd->redir_files = NULL;
	cmd->redirections = 0;
	cmd->tokens = NULL;

	tokens = tokenize(command); // -->per command
	if (tokens == NULL)
		return (NULL);
	cmd->tokens = tokens;
	//test_print_tokens(tokens);
	set_redirections_type(cmd, tokens);
	//printf("Redir count: %d\n", cmd->n_redir);
	if (cmd->n_redir != 0)
		configure_redirections(cmd, tokens);
	expander(cmd, tokens);
	// if (expander(cmd, tokens) == 1)
	// {
	// 	printf("ddd\n");
	// 	//return (NULL);
	// }

	remove_outer_quotes(tokens);

	//printf("Start of build_command\n");
	cmd->n_args = n_args(tokens);
	//printf("Nr of args : %d\n", cmd->n_args);
	cmd = configure_command_data(cmd, tokens);
	//configure command
	//printf("End of build_command\n");
	return (cmd);
}

int	command_builder(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd) * data->n_cmd); // FREE
	malloc_calls++;
	if (cmd == NULL)
		raise_error_free("Failed to allocate memory for cmd structs", data);
	data->commands = cmd;
	cmd->data = data;
	i = 0;
	while(i < data->n_cmd)
	{
		if (data->n_cmd == 1) //only 1 command
		{
			build_command(cmd + i, data->input);
			// if (build_command(cmd + i, data->input) == NULL)
			// 	return (1);

			// printf("Start of command_builder\n");
			//break ;
			// if (build_command(cmd + i, data->input) == NULL)
			// raise_error_free("Failed to build command", data);
		}
		else //multiple commands
		{
			build_command(cmd + i, data->input_split_by_cmds[i]);
			// if(build_command(cmd + i, data->input_split_by_cmds[i]) == NULL)
			// 	return (1);
			// if (build_command(cmd + i, data->input_split_by_cmds[i]) == NULL)
			// 	raise_error_free("Failed to build command", data);
			
		}
		i++;
	}
	//printf("End of command_builder\n");
	return (0);
}

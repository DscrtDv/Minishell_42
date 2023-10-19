#include"../../include/minishell.h"

static int init_cmd_array(t_data *data)
{
	get_n_cmd(data);
	//printf("%d\n", data->n_cmd);
	data->input_split_by_cmds = malloc(sizeof(char *) * (data->n_cmd + 1)); // FREE
	if (data->input_split_by_cmds == NULL)
	{
		printf("Failed to allocate memory for the input_split_by_cmds\n"); //-->FREE
		return (1);
	}
	return (0);
}

int	split_by_commands(t_data *data)
{
	int		i;
	int		j;
	char	*input;

	input = data->input;
	if (init_cmd_array(data) != 0)
		return (1);
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
		{
			if (split_into_cmds(data, input, i, &j) == 1)
				return (1);
		}
		i++;
	}
	data->input_split_by_cmds[j] = NULL;
	return (0);
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
	// if (command[*i] == '\0')
	// 	break ;
	word = isolate_token(command, *i);
	if (word == NULL)
		return (NULL);
	new_token = create_token(word);
	if (new_token == NULL)
	{
		printf("Failed to create new_token node\n");
		return (NULL);
	}
	insert_at_end(tokens, new_token);
	return (*tokens);
}

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
	word = isolate_redir(command, command[*i], i, word);
	if (word == NULL)
		return (NULL);
	new_token = create_token(word);
	if (new_token == NULL)
	{
		free(word);
		word = NULL;
		printf("Failed to create new_token node\n"); //and free
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

// static void tokenize_loop(char *command, t_token **tokens, int *i)
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

// t_token *valid_redirections(t_tokens *tokens, char *command, int *i)
// { 
//  	while (ft_isspace(command[i]) == 1)
// 		(i)++;
// 	if (command[i] == '>' || command[i] == '<')
// 		continue ;
// 	if (command[i] == '\0')
// 		break ;
// 	tokens = save_token(&tokens, command, &i);
// 	if (tokens == NULL)
// 		return (NULL);
// 	return (tokens);
// }

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
			tokens = save_redir(&tokens, command, &i);
			if (tokens == NULL)
				return (NULL);
			continue ;
		}
		i++;
	}
	return (tokens);
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

static int single_quotes_found(char **clean_str, char **new_str, char *str, int *i)
{
	int		index_l;
	int		index_r;

	index_l = 0;
	index_r = 0;
	index_l = *i;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '\'')
		(*i)++;
	index_r = *i;
	*clean_str = ft_substr(str, index_l + 1, index_r - index_l - 1);
	if (*clean_str == NULL)
	{
		if (*new_str[0] != '\0')
			free(*new_str);
		return (-1);
	}
	*new_str = ft_strjoin(*new_str, *clean_str);
	if (*new_str == NULL)
	{
		free(*clean_str);
		return (-1);
	}
	free(*clean_str);
	return (index_r);
}

static int double_quotes_found(char **clean_str, char **new_str, char *str, int *i)
{
	int		index_l;
	int		index_r;

	index_l = 0;
	index_r = 0;
	index_l = *i;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '\"')
		(*i)++;
	index_r = *i;
	*clean_str = ft_substr(str, index_l + 1, index_r - index_l - 1);
	if (*clean_str == NULL)
	{
		if (*new_str[0] != '\0')
			free(*new_str);
		return (-1);
	}
	*new_str = ft_strjoin(*new_str, *clean_str);
	if (*new_str == NULL)
	{
		free(*clean_str);
		return (-1);
	}
	free(*clean_str);
	return (index_r);
}

static int no_quotes_found(char **clean_str, char **new_str, char *str, int *i)
{
	*clean_str = ft_substr(str, *i, 1);
	if (*clean_str == NULL)
	{
		if (*new_str[0] != '\0')
			free(*new_str);
		return (-1);
	}
	*new_str = ft_join(*new_str, *clean_str);
	if (*new_str == NULL)
	{
		free(*clean_str);
		return (-1);
	}
	free(*clean_str);
	return (0);
}

static int move_index(char *str, int index, int index_r)
{
	int	i;

	i = index;
	if (str[i] != '\'' && str[i] != '\"')
		i++;
	else
		i = index_r + 1;
	return (i);
}

static int remove_quote_selector(char *str, char **clean_str, char **new_str, int *i)
{
	int	index_r;

	index_r = 0;
	if (str[*i] == '\'')
	{
		index_r = single_quotes_found(clean_str, new_str, str, i);
		if (index_r == -1)
			return (-1);
	}
	else if (str[*i] == '\"')
	{
		index_r = double_quotes_found(clean_str, new_str, str, i);
		if (index_r == -1)
			return (-1);
	}
	else
	{
		no_quotes_found(clean_str, new_str, str, i);
		if (index_r == -1)
			return (-1);			
	}
	return (index_r);
}

static int remove_quotes_loop(char *str, char **clean_str, char **new_str)
{
	int		i;
	int		index_r;

	i = 0;
	index_r = 0;
	while (str && str[i])
	{
		index_r = remove_quote_selector(str, clean_str, new_str, &i);
		if (index_r == -1)
		{
			//free
			return (1);
		}
		i = move_index(str, i, index_r);
	}
	return (0);
}

int remove_outer_quotes(t_token *tokens)
{
	char 	*clean_str;
	char	*new_str;
	char	*str;

	while (tokens != NULL)
	{
		str = tokens->str;
		new_str = "";
		clean_str = NULL;
		if (remove_quotes_loop(str, &clean_str, &new_str) != 0)
			return (1);
		if (tokens->str[0] != '\0')
			free(tokens->str);
		tokens->str = ft_strdup(new_str);
		if (new_str[0] != '\0')
			free(new_str);
		tokens = tokens->next;
	}
	return (0);
}

static int remove_outer_quotes_redir(t_cmd *cmd)
{
	char 	*clean_str;
	char	*new_str;
	int		i;

	i = 0;
	if (cmd->redir_files == NULL)
		return (0);
	while (cmd->redir_files[i] != NULL)
	{
		new_str = "";
		clean_str = NULL;
		if (remove_quotes_loop(cmd->redir_files[i], &clean_str, &new_str) != 0)
			return (1);
		free(cmd->redir_files[i]);
		cmd->redir_files[i] = ft_strdup(new_str);
		if (new_str[0] != '\0')
			free(new_str);
		i++;
	}
	return (0);
}

static void set_redirections_out(t_cmd *cmd, t_token *tokens)
{
	while (tokens && tokens != NULL)
	{
		if (ft_strncmp(tokens->str, ">", 1) == 0 && ft_strlen(tokens->str) == 1)
		{
			tokens->type = OUT_SINGLE;
			cmd->n_redir++;
		}
		else if (ft_strncmp(tokens->str, ">>", 2) == 0
			&& ft_strlen(tokens->str) == 2)
		{
			tokens->type = OUT_DOUBLE;
			cmd->n_redir++;
		}
		tokens = tokens->next;
	}
}

static void set_redirections_in(t_cmd *cmd, t_token *tokens)
{
	while (tokens && tokens != NULL)
	{
		if (ft_strncmp(tokens->str, "<", 1) == 0 && ft_strlen(tokens->str) == 1)
		{
			tokens->type = IN_SINGLE;
			cmd->n_redir++;
		}
		else if (ft_strncmp(tokens->str, "<<", 2) == 0
			&& ft_strlen(tokens->str) == 2)
		{
			tokens->type = IN_DOUBLE;
			cmd->n_redir++;
			cmd->has_hd = true;
		}
		tokens = tokens->next;
	}
}

static void	set_redirections_type(t_cmd *cmd, t_token *tokens)
{
	set_redirections_in(cmd, tokens);
	set_redirections_out(cmd, tokens);
	// while (tokens && tokens != NULL)
	// {
	// 	if (ft_strncmp(tokens->str, ">", 1) == 0 && ft_strlen(tokens->str) == 1)
	// 	{
	// 		tokens->type = OUT_SINGLE;
	// 		cmd->n_redir++;
	// 	}
	// 	else if (ft_strncmp(tokens->str, ">>", 2) == 0 && ft_strlen(tokens->str) == 2)
	// 	{
	// 		tokens->type = OUT_DOUBLE;
	// 		cmd->n_redir++;
	// 	}
	// 	else if (ft_strncmp(tokens->str, "<", 1) == 0 && ft_strlen(tokens->str) == 1)
	// 	{
	// 		tokens->type = IN_SINGLE;
	// 		cmd->n_redir++;
	// 	}
	// 	else if (ft_strncmp(tokens->str, "<<", 2) == 0 && ft_strlen(tokens->str) == 2)
	// 	{
	// 		tokens->type = IN_DOUBLE;
	// 		cmd->n_redir++;
	// 	}
	// 	tokens = tokens->next;
	// }
}

static t_cmd *configure_redirections(t_cmd *cmd, t_token *tokens)
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
		if (tokens->type != -1)
		{
			cmd->redir_files[i] = ft_strdup(tokens->next->str);
			if (cmd->redir_files[i] == NULL)
				return (NULL);
			cmd->redirections[i] = tokens->type;
			i++;
		}
		tokens = tokens->next;
	}
	cmd->redir_files[i] = NULL;
	return (cmd);
}

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
	while (tokens != NULL && tokens->type == -1)
	{	
		cmd->args[i] = ft_strdup(tokens->str);
		if (cmd->args[i] == NULL)
			return (NULL);
		i++;
		tokens = tokens->next;
	}
	cmd->args[i] = NULL;
	return (cmd);
}

static void init_cmd_data(t_cmd *cmd, t_data *data)
{
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->tokens = NULL;
	cmd->redir_files = NULL;
	cmd->redirections = NULL;
	cmd->n_redir = 0;
	cmd->data = data;
}

static int build_command(t_cmd *cmd, t_data *data, char *command)
{
	t_token	*tokens;
	
	init_cmd_data(cmd, data);
	tokens = tokenize(command);
	if (tokens == NULL)
		return (1);
	cmd->tokens = tokens;
	set_redirections_type(cmd, tokens);
	//printf("%d\n", cmd->n_redir);
	if (cmd->n_redir != 0)
	{
		if (configure_redirections(cmd, tokens) == NULL)
			return (1);
	}
	if (expander(cmd, data) == 1)
		return (1);
	if (remove_outer_quotes(tokens) == -1)
		return (1);
	if (remove_outer_quotes_redir(cmd) == -1)
		return (1);
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
	
	cmd = malloc(sizeof(t_cmd) * data->n_cmd);
	if (cmd == NULL)
	{
		printf("Failed to allocate memory for cmd structs\n");
		return (1);
	}
	data->commands = cmd;
	cmd->has_hd = false;
	i = 0;
	while(i < data->n_cmd)
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

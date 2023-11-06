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

int	_lstsize(t_token *lst)
{
	int		size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
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
	while (tokens != NULL)
	{
		if (tokens->type == -2)
		{
			tokens = tokens->next;
			continue ;
		}
		if (tokens->type == -1)
			args_count++;
		tokens = tokens->next;
	}
	//printf("n_args: %d\n", args_count);
	return (args_count);
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
	while (tokens != NULL)
	{	
		if (tokens->type == -1)
		{
			cmd->args[i] = ft_strdup(tokens->str);
			if (cmd->args[i] == NULL)
				return (NULL);
			i++;
		}
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
	data->cmd_initialized = true;
}

static int build_command(t_cmd *cmd, t_data *data, char *command)
{
	t_token	*tokens;
	
	init_cmd_data(cmd, data);
	tokens = tokenize(command); //PROTECTED
	if (tokens == NULL)
		return (1);
	cmd->tokens = tokens;
	set_redirections_type(cmd, tokens);
	if (cmd->n_redir != 0)
	{
		if (configure_redirections(cmd, tokens) == NULL)
			return (1);
	}
	if (expander(cmd, data) == 1) // PROTECTED
	{
		cmd->tokens = tokens;
		return (1);
	}
	if (remove_outer_quotes(tokens) == 1) // PROTECTED
	{
		cmd->tokens = tokens;
		return (1);
	}
	if (remove_outer_quotes_redir(cmd) == 1) // PROTECTED
		return (1);
	cmd->n_args = n_args(tokens);
	cmd = configure_command_data(cmd, tokens); // PROTECTED
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

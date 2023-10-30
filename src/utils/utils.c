
#include "../../include/minishell.h"

void print_db_array(t_data *data)
{
	int	i;

	i = 0;
	while(data->input_split_by_cmds[i])
	{
		printf("Command %d:%s\n", i, data->input_split_by_cmds[i]);
		i++;
	}
}

void	free_tokens(t_data *data)
{
	printf("FREE_TOKENS\n");
	t_token	*temp;
	int	i;

	if (data->commands == NULL)
		return ;
	i = 0;
	while (i < data->n_cmd && data->commands[i].tokens != NULL)
	{
		if (data->commands[i].tokens == NULL)
			break ;
		while (data->commands[i].tokens != NULL)
		{
			//printf("+++++\n");
			temp = data->commands[i].tokens;
			// if (temp->str[0] == '\0')
			// {
			// 	free(temp);
			// 	temp = NULL;
			// 	break ;
			// }
			data->commands[i].tokens = data->commands[i].tokens->next;
			if (temp->str[0] != '\0')
			{
				free(temp->str);
				temp->str = NULL;
			}
			free(temp);
			temp = NULL;
		}
		i++;
	}
}

void	_free_array(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_cmds_array(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		//printf("FREE CMDS ARRAY\n");
		free(data->commands[i].name);
		data->commands[i].name = NULL;
		free(data->commands[i].redirections);
		data->commands[i].redirections = NULL;
		_free_array(data->commands[i].redir_files);
		_free_array(data->commands[i].args);
		i++;
	}
	free(data->commands);
	data->commands = NULL;
}

void	free_all_parse(t_data *data)
{
	data->n_hd = 0;
	if (data->input[0] == '\0')
		return ;
	free(data->input);
	data->input = NULL;
	_free_array(data->input_split_by_cmds);
	//if (data->input != NULL)
	free_tokens(data);
	if (data->cmd_initialized == true)
		free_cmds_array(data);
	// if (data->hd_path)
	// 	free(data->hd_path);
	//free_list(data->env);
}

void raise_error_free(char *str, t_data *data)
{
	printf("%s\n", str);
	free_all_parse(data);
	exit(EXIT_FAILURE);
}

void raise_error(char *str)
{
	printf("%s\n", str);
	//exit(EXIT_FAILURE);
}

int	get_end_token_index(char *input, int i)
{
	while (input[i])
	{
		i++;
		if ((ft_strchr(" <>", input[i]) != 0) && (not_in_quotes(input, i) == true))
			return (i);
	}
	return (i);
}

char	*_isolate_token(char *input, int start, int end) //malloc  protected
{
	// (void)start;
	// (void)end;
	// (void)input;
	int		len;
	char	*token;
	
	len = end - start;
	token = ft_substr(input, start, len);
	// token = NULL;
	if (token == NULL)
	{
		printf("Error while isolating the redir token\n");
		return (NULL);
	}
	return (token);
}

char	*isolate_token(char *command, int i) //malloc protected
{
	// (void)i;
	// (void)command;

	int		end_pos;
	int		len_token;
	char	*token;
	
	end_pos = get_end_token_index(command, i);
	len_token = end_pos - i;
	token = ft_substr(command, i, len_token);
	// token = NULL;
	if (token == NULL)
	{
		printf ("Error while isolating the token\n");
		return (NULL);
	}
	return (token);
}

char *isolate_redir(char *command, char c, int *i, char *word)
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

void	get_n_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->input && data->input[i])
	{
		if (data->input[i] == '|' && not_in_quotes(data->input, i) == true)
			data->n_cmd++;
		i++;
	}
}

int	get_end_cmd_index(char *input, int i)
{
	while(input[i])
	{
		i++;
		if (input[i] == '|' && not_in_quotes(input, i) == true)
			return (i);
	}
	return (i);
}

int	split_lefmost_cmd(t_data *data, char *input, int i, int *j)
{
	// (void)i;
	// (void)input;
	data->input_split_by_cmds[*j] = ft_substr(input, 0, i);
	//data->input_split_by_cmds[*j] = NULL;
	if (data->input_split_by_cmds[*j] == NULL)
	{
		printf("Failed to split by commands\n");
		return (1);
	}
	(*j)++;
	return (0);
}

int	split_into_cmds(t_data *data, char *input, int i, int *j)
{
	// (void)i;
	// (void)input;

	int	command_index_end;
	int	len_cmd;

	command_index_end = get_end_cmd_index(input, i);
	len_cmd = command_index_end - i;
	data->input_split_by_cmds[*j] = ft_substr(input, i + 1, len_cmd - 1);
	// data->input_split_by_cmds[*j] = NULL;
	if (data->input_split_by_cmds[*j] == NULL)
	{
		printf("Failed to split by commands\n");
		return (1);
	}
	(*j)++;
	return (0);
}


#include"../../include/minishell.h"

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

void	free_all_parse(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->input_split_by_cmds)
		ft_free_array(data->input_split_by_cmds);
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
	exit(EXIT_FAILURE);
}

int	get_end_token_index(char *input, int i)
{
	while(input[i])
	{
		i++;
		if ((ft_strchr(" <>", input[i]) != 0) && (not_in_quotes(input, i) == true))
			return (i);
	}
	return (i);
}

char	*_isolate_token(char *input, int start, int end)
{
	int		len;
	char	*token;
	
	len = end - start;
	token = ft_substr(input, start, len);
	if (token == NULL)
		raise_error("Error while isolating the token");
	//printf("TOKEN= %s\n", token);
	//free(token);
	return(token);
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
		raise_error("Error while isolating the token");
	
	//printf("TOKEN= %s\n", token);
	//free(token);
	return(token);
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

void	get_cmd_count(t_data *data)
{
	int	i;

	i = 0;
	while (data->input && data->input[i])
	{
		if (data->input[i] == '|' && not_in_quotes(data->input, i) == true)
			data->cmd_count++;
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

void	split_lefmost_cmd(t_data *data, char *input, int i, int *j)
{
	data->input_split_by_cmds[*j] = ft_substr(input, 0, i);
	if (data->input_split_by_cmds[*j] == NULL)
		raise_error_free("Failed to split by commands", data);
	(*j)++;
}

void	split_into_cmds(t_data *data, char *input, int i, int *j)
{
	int	command_index_end;
	int	len_cmd;

	command_index_end = get_end_cmd_index(input, i);
	len_cmd = command_index_end - i;
	data->input_split_by_cmds[*j] = ft_substr(input, i + 1, len_cmd - 1);
	if (data->input_split_by_cmds[*j] == NULL)
		raise_error_free("Failed to split by commands", data);
	(*j)++;
}





//-------OLD-------//

// void	split_by_delimiters_second_verson(t_data *data)
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

// void get_rows_input(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->input[i])
// 	{
// 		if (data->input[i] == '|')
// 			data->rows_split_input++;
// 		i++;
// 	}
// }

// void	isolate_token(char *command, int i)
// {
// 	int		end_pos;
// 	int		len_token;
// 	char	*token;
	
// 	end_pos = get_end_token_index(command, i);
// 	len_token = end_pos - i;
// 	token = ft_substr(command, i, len_token);
// 	if (token == NULL)
// 		raise_error("Error while isolating the token");
	
// 	printf("TOKEN= %s\n", token);
// 	free(token);
// }

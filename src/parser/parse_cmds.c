
#include"../../include/minishell.h"

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
	data->input_split_by_cmds[*j] = ft_substr(input, 0, i);
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
	int	command_index_end;
	int	len_cmd;

	command_index_end = get_end_cmd_index(input, i);
	len_cmd = command_index_end - i;
	data->input_split_by_cmds[*j] = ft_substr(input, i + 1, len_cmd - 1);
	if (data->input_split_by_cmds[*j] == NULL)
	{
		printf("Failed to split by commands\n");
		return (1);
	}
	(*j)++;
	return (0);
}

int init_cmd_array(t_data *data)
{
	get_n_cmd(data);
	data->input_split_by_cmds = malloc(sizeof(char *) * (data->n_cmd + 1));
	if (data->input_split_by_cmds == NULL)
	{
		printf("Failed to allocate memory for the input_split_by_cmds\n");
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
		if ((j == 0 ) && (input[i] == '|' && not_in_quotes(input, i) == true))
		{
			if (split_lefmost_cmd(data, input, i, &j) == 1)
				return (1);
		}
		if ((input[i] == '|' && not_in_quotes(input, i) == true))
		{
			if (split_into_cmds(data, input, i, &j) == 1)
				return (1);
		}
		i++;
	}
	data->input_split_by_cmds[j] = NULL;
	return (0);
}

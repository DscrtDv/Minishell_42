
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

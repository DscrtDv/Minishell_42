
#include"../../include/minishell.h"

bool	check_quotes(char *input, char c, int current_pos)
{
	int	i;
	int	quotes_count;

	i = 0;
	quotes_count = 0;
	while(i < current_pos)
	{
		if (input[i] == c)
			quotes_count++;
		i++;
	}
	if (quotes_count % 2 == 0)
		return (true);
	return (false);
}

bool	not_in_quotes(char *input ,int current_pos)
{
	bool	not_in_single_quotes;
	bool	not_in_double_quotes;
	
	not_in_single_quotes = check_quotes(input, '\'', current_pos);
	not_in_double_quotes = check_quotes(input, '\"', current_pos);
	return (not_in_single_quotes && not_in_double_quotes);
}

bool	not_in_single_quotes(char *input, int current_pos)
{
	bool	not_in_single_quotes;

	int	i;

	i = 0;
	while (i < current_pos)
	{
		i++;
	}
	not_in_single_quotes = check_quotes(input, '\'', current_pos);
	return (not_in_single_quotes);
}

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
	return (args_count);
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

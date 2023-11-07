#include"../../include/minishell.h"

static bool valid_single_quote(char *str, int pos)
{
	int	i;
	int	count;

	i = pos;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			count++;
		i++;
	}
	i = pos;
	while (i >= 0)
	{
		if (str[i] == '\"')
			count++;
		i--;
	}
	if (count % 2 == 0 && count > 0)
		return (true);
	return (false);
}

static bool valid_double_quote(char *str, int pos)
{
	int	i;
	int	count;

	i = pos;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	i = pos;
	while (i >= 0)
	{
		if (str[i] == '\'')
			count++;
		i--;
	}
	if (count % 2 == 0  && count > 0)
		return (true);
	return (false);
}

bool	check_double_quotes(char *input, size_t current_pos)
{
	size_t	i;
	int	quotes_count;

	i = 0;
	quotes_count = 0;
	while(i < current_pos)
	{
		if (input[i] == '\"' && valid_double_quote(input, i) == false)
			quotes_count++;
		i++;
	}
	if (quotes_count % 2 == 0)
		return (true);
	return (false);
}

bool	check_single_quotes(char *input, size_t current_pos)
{
	size_t	i;
	int	quotes_count;

	i = 0;
	quotes_count = 0;
	while(i < current_pos)
	{
		if (input[i] == '\'' && valid_single_quote(input, i) == false)
			quotes_count++;
		i++;
	}
	if (quotes_count % 2 == 0)
		return (true);
	return (false);
}

bool	closed_quotes(t_data *data)
{
	int		last_index_pos;
	bool	unclosed_single_quotes;
	bool	unclosed_double_quotes;

	last_index_pos = ft_strlen(data->input);
	unclosed_single_quotes = check_single_quotes(data->input, last_index_pos);
	unclosed_double_quotes = check_double_quotes(data->input, last_index_pos);
	return (unclosed_double_quotes && unclosed_single_quotes);
}

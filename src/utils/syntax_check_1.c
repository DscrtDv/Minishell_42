
#include"../../include/minishell.h"

bool	correct_pipes(t_data *data)
{
	int		i;
	int		j;
	char	*input;

	i = 0;
	j = 0;
	input = data->input;
	while (ft_isspace(input[i]) == 1)
		i++;
	if (input[i] == '|' && not_in_quotes(input, i) == true)
		return (false);
	while(input[i])
	{
		if(input[i] == '|' && not_in_quotes(input, i) == true)
		{
			j = i + 1;
            while ((input[j] != '\0') && (ft_isspace(input[j]) == 1))
                j++;
            if ((input[j] == '|') || (input[j] == '\0'))
				return (false);
		}
		i++;
	}
	return (true);
}

static bool correct_redir_out(char *input, int i)
{
	int j;
	
	j = i + 1;
	if (input[j] == '>')
		j++;
    while ((input[j] != '\0') && (ft_isspace(input[j]) == 1))
	{
    	j++;
	}
	if (input[j] == '>')
	{
		printf("Syntax error: Unexpected token '>'\n");
		return (false);
	}
	if (input[j] == '<')
	{
		printf("Syntax error: Unexpected token '<'\n");
		return (false);
	}
    if (input[j] == '\0')
	{
        printf("Syntax error: Unexpected token '>'\n");
		return (false);
	}
	return (true);
}

static bool correct_redir_in(char *input, int i)
{
	int j;
	
	j = i + 1;
	if (input[j] == '<')
		j++;
    while ((input[j] != '\0') && (ft_isspace(input[j]) == 1))
	{
        j++;
	}
	if (input[j] == '<')
	{
		printf("Syntax error: Unexpected token '<'\n");
		return (false);
	}
	if (input[j] == '>')
	{
		printf("Syntax error: Unexpected token '>'\n");
		return (false);
	}
    if (input[j] == '\0')
	{
        printf("Syntax error: Unexpected token '<'\n");
		return (false);
	}
	return (true);
}

bool	correct_redir(t_data *data)
{
	int		i;
	char	*input;

	i = 0;
	input = data->input;
	while(input[i])
	{
		if((input[i] == '>') && (not_in_quotes(input, i) == true))
		{
			if (correct_redir_out(input, i) == false)
				return (false);
		}
		if((input[i] == '<') && (not_in_quotes(input, i) == true))
		{
			if (correct_redir_in(input, i) == false)
				return (false);
		}
		i++;
	}
	return (true);
}

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

bool correct_dollar(t_data *data)
{
	int		i;
	char	*input;

	i = 0;
	input = data->input;
	while (input[i])
	{
		if (input[i] == '$' && (not_in_single_quotes(input, i) == true))
		{
			i++;
			if (input[i] && (input[i] == '$' && (not_in_single_quotes(input, i) == true)))
			{
				printf("Syntax error: Unexpected token '$' \n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

int	check_syntax(t_data *data)
{
	if (closed_quotes(data) == false)
	{
		printf("Syntax error: Unclosed quotes detected\n");
		exit_code = 258;
		return (-1);
	}
	if (correct_pipes(data) == false)
	{
		printf("Syntax error: Unexpected token '|'\n");
		exit_code = 258;
		return (-1);
	}
	if (correct_redir(data) == false)
	{
		exit_code = 258;
		return (-1);
	}
	if (correct_dollar(data) == false)
	{
		exit_code = 258;
		return (-1);
	}
	return (0);
}

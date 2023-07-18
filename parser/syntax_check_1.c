
#include"../minishell.h"


void	check_correct_pipe(t_data *data)
{
	int		i;
	int		j;
	char	*input;

	i = 0;
	j = 0;
	input = data->input;
	while (ft_isspace(input[i]) == 1)
		i++;
	if (input[i] == '|' && not_in_quotes(input, i) == 1)
		raise_error_free("Syntax error: Unexpected token '|' ", data);
	while(input[i])
	{
		if(input[i] == '|' && not_in_quotes(input, i) == 1)
		{
			j = i + 1;
            while ((input[j] != '\0') && (ft_isspace(input[j]) == 1))
                j++;
            if ((input[j] == '|') || (input[j] == '\0'))
                raise_error_free("Syntax error: Unexpected token '|' ", data);
		}
		i++;
	}
}

void 	check_redir_out(t_data *data, char *input, int i)
{
	int j;
	
	j = i + 1;
	if (input[j] == '>')
		j++;
    while ((input[j] != '\0') && (ft_isspace(input[j]) == 1))
        j++;
	if (input[j] == '>')
		raise_error_free("Syntax error: Unexpected token '>' ", data);
	if (input[j] == '<')
		raise_error_free("Syntax error: Unexpected token '<' ", data);
    if (input[j] == '\0')
        raise_error_free("Syntax error: Unexpected token '>' ", data);
}

void 	check_redir_in(t_data *data, char *input, int i)
{
	int j;
	
	j = i + 1;
	if (input[j] == '<')
		j++;
    while ((input[j] != '\0') && (ft_isspace(input[j]) == 1))
        j++;
	if (input[j] == '<')
		raise_error_free("Syntax error: Unexpected token '<' ", data);
	if (input[j] == '>')
		raise_error_free("Syntax error: Unexpected token '>' ", data);
    if (input[j] == '\0')
        raise_error_free("Syntax error: Unexpected token '<' ", data);
	
}

void	check_correct_redir(t_data *data)
{
	int		i;
	char	*input;

	i = 0;
	input = data->input;
	while(input[i])
	{
		if((input[i] == '>') && (not_in_quotes(input, i) == 1))
			check_redir_out(data, input, i);
		if((input[i] == '<') && (not_in_quotes(input, i) == 1))
			check_redir_in(data, input, i);
		i++;
	}
}



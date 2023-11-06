
#include "../../include/minishell.h"

void initialize_exp_data(t_exp_data *exp, t_data *data)
{
	exp->start = 0;
	exp->end = 0;
	exp->valid_expansion = 0;
	exp->dollar_out = true;
	exp->mem_error = false;
	exp->appended_str = "";
	exp->expanded_str = NULL;
	exp->env_key = NULL;
	exp->env_value = NULL;
	exp->data = data;
}

void set_start(t_exp_data *exp, char *str, int *i)
{
	if (str[*i] == '{')
	{
		exp->dollar_out = false;
		(*i)++;
	}
	if ((*i > 0) && (str[*i - 1] == '{'))
		exp->start = *i - 1;
	else
		exp->start = *i;
	// printf("start[%i] = %c\n", exp->start , str[exp->start]);
	(*i)++;
}

void set_end(t_exp_data *exp, char *str, int *i)
{
	if ((str[*i] == '$') || (str[*i] == ' ') || (str[*i] == '\0')
		|| (str[*i] == '\'') || (str[*i] == '\"'))
	{
		exp->end = *i - 1;
	}
	else if (str[*i] == '}' || str[*i] == '{')
		exp->end = *i;
	if (str[*i] == '}' && str[exp->start] != '$')
		exp->dollar_out = false;
}

bool curly_braces_closed(char *input, int index)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(i < index)
	{
		if (input[i] == '{' && not_in_quotes(input, index) == true)
			count++;
		if (input[i] == '}' && not_in_quotes(input, index) == true)
			count--;
		i++;
	}
	if (count == 0)
		return (true);
	return (false);
}

void env_value_not_found(t_exp_data *exp, char *str, int i)
{
	// printf("str[%d] = %c\n", i, str[i]);
	free(exp->env_key);
	free(exp->env_value);
	if (str[exp->start] == '{')
		exp->appended_str = ft_append_char(exp->appended_str, '{');
	if ((ft_strlen(str) == 1 && str[exp->start] == '$') || ((ft_strlen(str) >= 3)
		&& str[exp->start] == '{' && str[exp->start + 1] == '$' && str[exp->start + 2] == '}'))
	{
		exp->appended_str = ft_append_char(exp->appended_str, '$');
	}
	else if (ft_strlen(str) == 3 && (str[0] == '\"' && str[2] == '\"'))
	{
		exp->appended_str = ft_append_char(exp->appended_str, '$');
	}
	else if ((i > 0 && str[i - 1] == '$') && not_in_quotes(str, i - 1) == false)
	{
		exp->appended_str = ft_append_char(exp->appended_str, '$');
	}
}

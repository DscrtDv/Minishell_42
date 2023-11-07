
#include"../../include/minishell.h"

int expand_heredoc_line_loop(t_exp_data *exp, t_data *data, char *str, int *i)
{
	while(str && str[*i])
	{
		exp->mem_error = false;
		exp->dollar_out = true;
		if ((((str[*i] == '{' && str[*i + 1] == '$') || (str[*i] == '$'))
			&& not_in_single_quotes(str, *i) == true))
		{
			if (valid_expansion(exp, data, str, i) == -1)
				return (free(exp), 1);
			else if (exp->valid_expansion == -2)
				continue ;
		}
		else
		{
			if (append_helper(exp, str, i) == 1)
			{
				if (exp->mem_error == true)
					return (free(exp), 1);
				continue ;
			}
		}
		(*i)++;
	}
	return (0);
}

char *expand_heredoc_line(char *str, t_data *data)
{
	int 			i;
	char			*expanded_str;
	t_exp_data		*exp;

	expanded_str = NULL;
	exp = malloc(sizeof(t_exp_data));
	if (exp == NULL)
		return (NULL);
	initialize_exp_data(exp, data, &i);
	if (expand_heredoc_line_loop(exp, data, str, &i) != 0)
		return (NULL);
	expanded_str = exp->appended_str;
	return (free(exp), expanded_str);
}

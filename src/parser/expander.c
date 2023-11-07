
#include "../../include/minishell.h"

int append_helper(t_exp_data *exp, char *str, int *i)
{
	if (append_check(exp, str, *i) != 0)
	{
		(*i)++;
		return (1);
	}
	exp->appended_str = ft_append_char(exp->appended_str, str[*i]);
	if (exp->appended_str == NULL)
	{
		exp->mem_error = true;
		return (1);
	}
	return (0);
}

static int assign_new_str(char **original_str, char *appended_str)
{
	if (appended_str[0] != '\0')
	{
		free(*original_str);
		*original_str = ft_strdup(appended_str);
		if (*original_str == NULL)
		{
			free(appended_str);
			appended_str = NULL;
			return (1);
		}
		free(appended_str);
		appended_str = NULL;
	}
	else if (appended_str[0] == '\0')
	{
		free(*original_str);
		*original_str = "";
	}
	return (0);
}

static int	expander_loop(t_exp_data *exp, char *str, t_data *data, int i)
{
	i = 0;
	while(str && str[i])
	{
		exp->mem_error = false;
		exp->dollar_out = true;
		if ((((str[i] == '{' && str[i + 1] == '$') || (str[i] == '$'))
			&& not_in_single_quotes(str, i) == true))
		{
			if (valid_expansion(exp, data, str, &i) == -1)
				return (1);
			else if (exp->valid_expansion == -2)
				continue ;
		}
		else
		{
			if (append_helper(exp, str, &i) == 1)
			{
				if (exp->mem_error == true)
					return (1);
				continue ;
			}
		}
		i++;
	}
	return (0);
}

int	expander(t_cmd *cmd, t_data *data)
{
	int			i;
	char		*str;
	t_exp_data	*exp;

	exp = malloc(sizeof(t_exp_data));
	if (exp == NULL)
		return (1);
	while (cmd->tokens != NULL)
	{
		str = cmd->tokens->str;
		initialize_exp_data(exp, data, &i);
		if (expander_loop(exp, str, data, i) != 0)
		{
			free(exp);
			return (1);
		}
		if (assign_new_str(&cmd->tokens->str, exp->appended_str) != 0)
		{
			free(exp);
			return (1);
		}
		cmd->tokens = cmd->tokens->next;
	}
	free(exp);
	return (0);
}

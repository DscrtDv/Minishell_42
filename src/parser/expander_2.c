
#include "../../include/minishell.h"

static char	*get_env_key(char *input, int *i, t_exp_data *exp)
{
	int		var_len;
	int		j;
	char	*var_name;

	if (input[*i] == '{')
		(*i)++;
	var_len = 0;
	j = (*i);
	while (input[j] && input[j] != ' ' && input[j] != '\"' && input[j] != '\''
		&& input[j] != '$' && input[j] != '}' && input[j] != '{')
	{
		var_len++;
		j++;
	}
	var_name = malloc(sizeof(char) * (var_len + 1)); //protected
	if (var_name == NULL)
	{
		exp->mem_error = true;
		return (NULL);
	}
	j = 0;
	// printf("----[%d]: %c\n", *i, input[*i]);
	// printf("val_len: %d\n", var_len);
	while (j < var_len)
	{
		var_name[j] = input[*i];
		(*i)++;
		j++;
		if (input[*i - 1] == '?')
			break ;
	}
	var_name[j] = '\0';
	return (var_name);
}

static int get_key_helper(t_exp_data *exp, char *str, int *i)
{
	exp->env_key = get_env_key(str, i, exp);
	//printf("ENV_KEY: %s\n", exp->env_key);
	if (exp->env_key == NULL)
	{
		raise_error("env_var_name returned NULL");
		return (1);
	}
	return (0);
}

static int expand_str(t_exp_data *exp, char *str, int *i)
{
	exp->expanded_str = allocate_new_str(str + exp->start, exp->env_value, exp->start, exp->end); //PROTECTED
	if (exp->expanded_str == NULL)
	{
		exp->mem_error = true;
		return (1);
	}
	if (exp->dollar_out == false && str[exp->start] != '$' && str[*i] == '}')
	{
		exp->expanded_str = ft_append_char(exp->expanded_str, '}'); //PROTECTED
		if (exp->expanded_str == NULL)
		{
			exp->mem_error = true;
			return (1);
		}
	}
	exp->appended_str = ft_join(exp->appended_str, exp->expanded_str);//PROTECTED
	if (exp->appended_str == NULL)
	{
		free(exp->expanded_str);
		exp->mem_error = true;
		return (1);
	}
	// printf("expanded_str: %s\n", exp->expanded_str);
	// printf("appended_str: %s\n", exp->appended_str);

	*i = exp->end;
	// printf("i end[%i] = %c\n", *i, str[*i]);
	free(exp->expanded_str);
	free(exp->env_key);
	free(exp->env_value);
	return (0);
}

char	*find_env_value(t_exp_data *exp, t_env *env)
{
	char	*value;

	value = NULL;
	while (env != NULL)
	{
		if (ft_strncmp(exp->env_key, env->key, ft_strlen(exp->env_key) + 1) == 0)
		{
			value = ft_strdup(env->val);
			if (value == NULL)
				return (NULL);
		}
		env = env->next;
	}
	return (value);
}

int	valid_expansion(t_exp_data *exp, t_data *data, char *str, int *i)
{
	exp->valid_expansion = 0;
	set_start(exp, str, i);
	if (get_key_helper(exp, str, i) == 1)
	{
		exp->valid_expansion = -1;
		return (-1) ;
	}
	exp->env_value = find_env_value(exp, *data->env);
	// printf("env_value: %s\n" , exp->env_value);
	if (exp->env_value == NULL)
	{
		env_value_not_found(exp, str, *i);
		//printf("ENV NOT FOUND\n");
		// printf("i[%i] = %c\n", *i - 1, str[*i - 1]);
		exp->valid_expansion = -2;
		return (-2) ;
	}
	set_end(exp, str, i);
	// printf("end[%i] = %c\n", exp->end , str[exp->end]);
	if (expand_str(exp, str, i) == 1)
	{
		free(exp->env_key);
		free(exp->env_value);
		if (exp->appended_str != NULL && exp->appended_str[0] != '\0')
			free(exp->appended_str);
		printf("Failed to allocate memory (expand_str)\n");
		return (-1);
	}
	return (0);
}

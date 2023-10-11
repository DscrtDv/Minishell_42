
#include "../../include/minishell.h"

static bool curly_braces_closed(char *input, int index)
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

static char	*get_env_key(char *input, int *i)
{
	int		var_len;
	int		j;
	char	*var_name;

	if (input[*i] == '{')
		(*i)++;
	var_len = 0;
	j = (*i);
	while (input[j] && input[j] != ' ' && input[j] != '\"' && input[j] != '$' && input[j] != '}' && input[j] != '{')
	{
		if (input[j] == '\'')
			break ;
		var_len++;
		j++;
	}
	var_name = malloc(sizeof(char) * (var_len + 1)); // FREE
	if (var_name == NULL)
		return (NULL);
	j = 0;
	while(j < var_len)
	{
		var_name[j] = input[(*i)];
		(*i)++;
		j++;
	}
	var_name[j] = '\0';
	return (var_name);
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

static char	*allocate_new_str(char *str, char *value, int start, int end)
{
	int		i;
	int		j;
	int		x;
	int		len_key;
	int		len_value;
	int		len_str;
	char	*new_str;

	len_key = end - start + 1;
	len_value = ft_strlen(value);
	len_str = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len_str - len_key + len_value + 1));
	if (new_str == NULL)
		return (NULL); 
	i = 0;
	j = 0;
	x = 0;
	while (str && str[i] && str[i] != '$')
		new_str[j++] = str[i++];
	while(x < len_value)
		new_str[j++] = value[x++];
	new_str[j] = '\0';
	return (new_str);
}

char	*ft_append_char(char *str, char c)
{
	size_t			i;
	size_t			j;
	char			*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	if (c != '\0')
		new_str[j] = c;
	new_str[++j] = '\0';
	if (str[0] != '\0')
	{
		free(str);
		str = NULL;
	}
	return (new_str);	
}

static void env_value_not_found(t_exp_data *exp, char *str)
{
	free(exp->env_key);
	free(exp->env_value);
	if (str[exp->start] == '{')
		exp->appended_str = ft_append_char(exp->appended_str, '{');
	if ((ft_strlen(str) == 1 && str[exp->start] == '$') || ((ft_strlen(str) >= 3)
		&& str[exp->start] == '{' && str[exp->start + 1] == '$' && str[exp->start + 2] == '}'))
	{
		exp->appended_str = ft_append_char(exp->appended_str, '$');
	}
	if (ft_strlen(str) == 3 && (str[0] == '\"' && str[2] == '\"'))
		exp->appended_str = ft_append_char(exp->appended_str, '$');
}

static bool append_check(t_exp_data *exp, char *str, int i)
{
	if (exp->env_value != NULL && ((str[i] == '}'
		&& (str[exp->start] == '$' && str[exp->start + 1] == '{'
			&& curly_braces_closed(str, i) == false))))
	{
		return (1);
	}
	if (exp->dollar_out == false && (exp->env_value != NULL && ((str[i] == '}'
		&& (str[exp->start] == '{' && str[exp->start + 1] == '$'
			&& curly_braces_closed(str, i) == false)))))
	{
		return (1);
	}
	if (exp->env_value == NULL
		&& (str[i] == '}' && str[exp->start] == '$' && str[i - 1] != '\"'))
	{
		if (i > 0 && (str[exp->start + 1] == '\"' || str[exp->start + 1] == '\''))
		{
			return (0);
		}
		return (1);
	}
	return (0);
}

static void set_start(t_exp_data *exp, char *str, int *i)
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
	//printf("start[%i] = %c\n", exp->start , str[exp->start]);
	(*i)++;
}

static void set_end(t_exp_data *exp, char *str, int *i)
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

static int get_key_helper(t_exp_data *exp, char *str, int *i)
{
	exp->env_key = get_env_key(str, i);
	//printf("ENV_KEY: %s\n", exp->env_key);
	if (exp->env_key == NULL)
	{
		raise_error("env_var_name returned NULL");
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
			return (1);
		free(appended_str);
	}
	else if (appended_str[0] == '\0')
	{
		free(*original_str);
		*original_str = "";
	}
	return (0);
}

static void initialize_exp_data(t_exp_data *exp, t_data *data)
{
	exp->start = 0;
	exp->end = 0;
	exp->valid_expansion = 0;
	exp->dollar_out = true;
	exp->appended_str = "";
	exp->expanded_str = NULL;
	exp->env_key = NULL;
	exp->env_value = NULL;
	exp->data = data;
}

char	*ft_join(char *s1, char const *s2)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 || !s2)
		return (0);
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, s1, len + 1);
	ft_strlcat(result, s2, len + 1);
	if (s1[0] != '\0')
	{
		free(s1);
		s1 = NULL;
	}
	return (result);
}

static int expand_str(t_exp_data *exp, char *str, int *i)
{
	exp->expanded_str = allocate_new_str(str + exp->start, exp->env_value, exp->start, exp->end);
	if (exp->expanded_str == NULL)
		return (1);
	if (exp->dollar_out == false && str[exp->start] != '$' && str[*i] == '}')
		exp->expanded_str[ft_strlen(exp->expanded_str)] = '}';
	exp->appended_str = ft_join(exp->appended_str, exp->expanded_str);
	if (exp->appended_str == NULL)
		return (1);
	*i = exp->end;
	free(exp->expanded_str);
	free(exp->env_key);
	free(exp->env_value);
	return (0);
}

// int	get_value_helper(t_exp_data *exp, t_cmd *cmd, char *str)
// {
// 	exp->env_value = find_env_value(exp, *cmd->data->env);
// 	if (exp->env_value == NULL)
// 	{
// 		env_value_not_found(exp, str); 
// 		return (1);
// 		//continue ;
// 	}
// 	return (0);
// }
int	valid_expansion(t_exp_data *exp, t_data *data, char *str, int *i)
{
	set_start(exp, str, i);
	if (get_key_helper(exp, str, i) == 1)
	{
		exp->valid_expansion = -1;
		return (-1) ;
	}
	exp->env_value = find_env_value(exp, *data->env);
	//printf("env_value: %s\n" , exp->env_value);
	if (exp->env_value == NULL)
	{
		env_value_not_found(exp, str);
		exp->valid_expansion = -2;
		return (-2) ;
	}
	set_end(exp, str, i);
	if (expand_str(exp, str, i) == 1)
		printf("Failed to allocate memory (expand_str)\n");
	return (0);
}

int	append_helper(t_exp_data *exp, char *str, int i)
{
	if (append_check(exp, str, i) == 1)
	{
		i++;
		return (1);
		//continue ;
	}
	//free(exp->env_key);
	//free(exp->env_value);
	exp->appended_str = ft_append_char(exp->appended_str, str[i]);
	return (0);
}

int	expander_loop(t_exp_data *exp, char *str, t_data *data)
{
	int i; 
	
	i = 0;
	while(str && str[i])
	{
		exp->dollar_out = true;
		if ((((str[i] == '{' && str[i + 1] == '$') || (str[i] == '$'))
			&& not_in_single_quotes(str, i) == true))
		{
			if (valid_expansion(exp, data, str, &i) == -1)
				break ;
			else if (exp->valid_expansion == -2)
				continue ;
		}
		else
		{
			if (append_helper(exp, str, i) == -1)
				continue ;
		}
		i++;
	}
	return (0);
}

int	expander(t_cmd *cmd, t_data *data)
{
	char		*str;
	t_exp_data	*exp;

	exp = malloc(sizeof(t_exp_data));
	if (exp == NULL)
		return (1);
	// initialize_exp_data(exp, data);
	while (cmd->tokens != NULL)
	{
		str = cmd->tokens->str;
		initialize_exp_data(exp, data);
		expander_loop(exp, str, data);
		//printf ("TOKEN: %s\n", str);
		assign_new_str(&cmd->tokens->str, exp->appended_str);
		cmd->tokens = cmd->tokens->next;
	}
	free(exp);
	return (0);
}

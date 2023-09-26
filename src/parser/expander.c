
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
	malloc_calls++;
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

char	*find_env_value(t_env *env, char *key)
{
	char	*value;

	value = NULL;
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, ft_strlen(key) + 1) == 0)
		{
			value = ft_strdup(env->val);
			if (value == NULL)
				return (NULL);
			malloc_calls++; //!!!
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

	new_str = NULL;
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
	return (new_str);	
}

static bool	bad_substitution(char *str, int curr_pos)
{
	int	i;

	i = 0;
	//printf("str[%i] = %c\n", i , str[i]);
	if (str[i] && str[curr_pos] == '$')
		i++;
	if (str[i] && str[curr_pos + 1] == '{')
		i++;
		
	//printf("str[%i] = %c\n", i , str[i]);
	while (str && str[i])
	{	
		//printf("1str[%i] = %c\n", i , str[i]);
		if (str[i] == '$')
			i++;
		if (str[i] == '{')
			i++;
		while (str[i] && str[i] != '}')
		{
			//printf("strrr[%i] = %c\n", i , str[i]);
			if ((ft_strchr(" \"\'~!@$^&*(){[];:|<>,./", str[i]) != 0) && curly_braces_closed(str, i) == false)
				return (true);
			i++;
		}
		//printf("2str[%i] = %c\n", i , str[i]);
		if (str[i] == '}')
			i++;
		//printf("3str[%i] = %c\n", i , str[i]);

		// while (str[i] == '\'' || str[i] == '\"')
		// 	i++;
		if (str[i] == '{')
		{
			while (str[i] && str[i] != '}')
				i++;
		}
		else if ((str[i] == '\"' || str[i] == '\'') || (str[i] == '$' && str[i + 1] != '$'))
		{
			i++;
			while (str[i] && str[i] != '$' && str[i] != '{')
				i++;
		}
		//else if (str[i] == '\"' || str[i] == '\'')
		// while (ft_isspace(str[i]) == 1)
		// 	i++;
		i++;
		//printf("4str[%i] = %c\n", i , str[i]);
	}
	return (false);
}

static void env_value_not_found(char **appended_str, char *str, int start)
{
	printf("Environment variable not found\n");//!!!
	if (str[start] == '{')
		*appended_str = ft_append_char(*appended_str, '{');
	if ((ft_strlen(str) == 1 && str[start] == '$') || ((ft_strlen(str) >= 3)
		&& str[start] == '{' && str[start + 1] == '$' && str[start + 2] == '}'))
	{
		*appended_str = ft_append_char(*appended_str, '$');
	} 
}

static bool append_check_one(char *str, char *env_value, int i, int start)
{
	if (env_value != NULL && ((str[i] == '}' && (str[start] == '{' &&
		str[start + 1] == '$' && curly_braces_closed(str, i) == false))))
	{
		return (false);
	}
	return (true);
}

static bool append_check_two(char *str, char *env_value, int i, int start)
{
	if (env_value == NULL &&
		(str[i] == '}' && str[start] == '$' && str[i - 1] != '\"'))
	{
		if (i > 0 && (str[start + 1] == '\"' || str[start + 1] == '\''))
			return (true);
		return (false);
	}
	return (true);
}

static int set_start(char *str, int *i, int *start, bool *dollar_outside)
{
	if (str[*i] == '{')
	{
		*dollar_outside = false;
		(*i)++;
	}
	if (*dollar_outside == true && str[*i + 1] == '{')
	{
		if (bad_substitution(str, *i) == true)
		{
			printf("Bad substituton.\n"); //FREE?
			return (1);
		}
	}
	if ((*i > 0) && (str[*i - 1] == '{'))
		*start = *i - 1;
	else
		*start = *i;
	printf("start[%i] = %c\n", *start , str[*start]);
	(*i)++;
	return (0);
}

static void set_end(char *str, int *i, int *end)
{
	if ((str[*i] == '$') || (str[*i] == ' ') || (str[*i] == '\0')
		|| (str[*i] == '\'') || (str[*i] == '\"'))
	{
		*end = *i - 1;
	}
	else if (str[*i] == '}' || str[*i] == '{')
		*end = *i;
}


static int get_env_helper(char **env_key, char *str, int *i)
{
	*env_key = get_env_key(str, i);
	printf("ENV_KEY: %s\n", *env_key);
	if (*env_key == NULL)
	{
		raise_error("env_var_name returned NULL");
		return (1);
	}
	return (0);
}

// int	value_checker(char **env_value, char **env_key, char *str, int start)
// {

// }

static void set_dollar_outside(char *str, int i, int start, bool *dollar_out)
{
	if (str[i] == '}' && str[start] != '$')
		*dollar_out = false;
}

// static char *add_curly_brace(char *str, int i, int start, bool *dollar_out)
// {
// 	if (dollar_outside_braces == false && str[start] != '$' && str[i] == '}')
// 					expanded_str[ft_strlen(expanded_str)] = '}';
// }

// static char *expand(t_cmd *cmd, char **appended_str, char **expanded_str, char *str)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	bool	dollar_outside_braces;
// 	char	*env_key;
// 	char	*env_value;
// 	while(str && str[i])       //-------------
// 	{
// 		dollar_outside_braces = true;
// 		if ((((str[i] == '{' && str[i + 1] == '$') || (str[i] == '$'))
// 			&& not_in_single_quotes(str, i) == true))
// 		{
// 			if (set_start(str, &i, &start, &dollar_outside_braces) == 1)
// 				break ;
// 			if (get_env_helper(&env_key, str, &i) == 1)
// 				break ;
// 			env_value = find_env_value(*cmd->data->env, env_key);
// 			if (env_value == NULL)
// 			{
// 				printf("ENV_VALUE: %s\n", env_value);
// 				free(env_key);
// 				free(env_value);
// 				env_value_not_found(&appended_str, str, start); 
// 				continue ;
// 			}
// 			set_end(str, &i, &end);
// 			set_dollar_outside(str, i, start, &dollar_outside_braces);
// 			expanded_str = allocate_new_str(str + start, env_value, start, end);
// 			if (dollar_outside_braces == false && str[start] != '$' && str[i] == '}')
// 				expanded_str[ft_strlen(expanded_str)] = '}';
// 			appended_str = ft_strjoin(appended_str, expanded_str);
// 			i = end;
// 			free(expanded_str);
// 			free(env_key);
// 			free(env_value);
// 		}
// 		else
// 		{
// 			if (((append_check_one(str, env_value, i, start) == false)
// 				&& dollar_outside_braces == false)
// 				|| append_check_two(str, env_value, i, start) == false)
// 			{
// 				i++;
// 				continue ;
// 			}
// 			appended_str = ft_append_char(appended_str, str[i]);
// 		}
// 		i++;
// 	}
// }


static int assign_new_str(char **original_str, char *appended_str)
{
	if (appended_str[0] != '\0')
	{
		free(*original_str);
		*original_str = ft_strdup(appended_str);
		if (*original_str == NULL)
		{
			printf("SdSDSDSD\n");
			return (1);
		}
		free(appended_str);
	}
	else if (appended_str[0] == '\0')
	{
		free(*original_str);
		*original_str = "";
	}
	return (0);
}

static void initialize_exp_data(t_exp_data *exp)
{
	exp->i = 0;
	exp->start = 0;
	exp->end = 0;
	exp->dollar_out = 0;
	exp->appended_str = "";
	exp->expanded_str = NULL;
}

int	expander(t_cmd *cmd, t_token *tokens)
{
	int			i;
	char		*str;
	t_exp_data	*exp;

	exp = malloc(sizeof(t_exp_data));
	if (exp == NULL)
		return (1);
	initialize_exp_data(exp);
	while (tokens != NULL)
	{
		exp->appended_str = "";
		exp->expanded_str = NULL;
		i = 0;
		str = tokens->str;
		while(str && str[i])
		{
			exp->dollar_out = true;
			if ((((str[i] == '{' && str[i + 1] == '$') || (str[i] == '$'))
				&& not_in_single_quotes(str, i) == true))
			{
				if (set_start(str, &i, &exp->start, &exp->dollar_out) == 1)
					break ;
				if (get_env_helper(&exp->env_key, str, &i) == 1)
					break ;
				exp->env_value = find_env_value(*cmd->data->env, exp->env_key);
				if (exp->env_value == NULL)
				{
					free(exp->env_key);
					free(exp->env_value);
					env_value_not_found(&exp->appended_str, str, exp->start); 
					continue ;
				}
				set_end(str, &i, &exp->end);
				set_dollar_outside(str, i, exp->start, &exp->dollar_out);
				exp->expanded_str = allocate_new_str(str + exp->start, exp->env_value, exp->start, exp->end);
				if (exp->dollar_out == false && str[exp->start] != '$' && str[i] == '}')
					exp->expanded_str[ft_strlen(exp->expanded_str)] = '}';
				exp->appended_str = ft_strjoin(exp->appended_str, exp->expanded_str);
				i = exp->end;
				free(exp->expanded_str);
				free(exp->env_key);
				free(exp->env_value);
			}
			else
			{
				if (((append_check_one(str, exp->env_value, i, exp->start) == false)
					&& exp->dollar_out == false)
					|| append_check_two(str, exp->env_value, i, exp->start) == false)
				{
					i++;
					continue ;
				}
				exp->appended_str = ft_append_char(exp->appended_str, str[i]);
			}
			i++;
		}
		assign_new_str(&tokens->str, exp->appended_str);
		tokens = tokens->next;
	}
	return(0);
}

// int	expander(t_cmd *cmd, t_token *tokens)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	bool	dollar_outside_braces;
// 	char	*str;
// 	char	*expanded_str;
// 	char	*appended_str;
// 	char	*env_key;
// 	char	*env_value;
	
// 	start = 0;
// 	end = 0;
// 	while (tokens != NULL)
// 	{
// 		appended_str = "";
// 		expanded_str = NULL;
// 		i = 0;
// 		str = tokens->str;
// 		while(str && str[i])
// 		{
// 			dollar_outside_braces = true;
// 			if ((((str[i] == '{' && str[i + 1] == '$') || (str[i] == '$'))
// 				&& not_in_single_quotes(str, i) == true))
// 			{
// 				if (set_start(str, &i, &start, &dollar_outside_braces) == 1)
// 					break ;
// 				if (get_env_helper(&env_key, str, &i) == 1)
// 					break ;
// 				env_value = find_env_value(*cmd->data->env, env_key);
// 				if (env_value == NULL)
// 				{
// 					free(env_key);
// 					free(env_value);
// 					env_value_not_found(&appended_str, str, start); 
// 					continue ;
// 				}
// 				set_end(str, &i, &end);
// 				set_dollar_outside(str, i, start, &dollar_outside_braces);
// 				expanded_str = allocate_new_str(str + start, env_value, start, end);
// 				if (dollar_outside_braces == false && str[start] != '$' && str[i] == '}')
// 					expanded_str[ft_strlen(expanded_str)] = '}';
// 				appended_str = ft_strjoin(appended_str, expanded_str);
// 				i = end;
// 				free(expanded_str);
// 				free(env_key);
// 				free(env_value);
// 			}
// 			else
// 			{
// 				if (((append_check_one(str, env_value, i, start) == false)
// 					&& dollar_outside_braces == false)
// 					|| append_check_two(str, env_value, i, start) == false)
// 				{
// 					i++;
// 					continue ;
// 				}
// 				appended_str = ft_append_char(appended_str, str[i]);
// 			}
// 			i++;
// 		}
// 		assign_new_str(&tokens->str, appended_str);
// 		tokens = tokens->next;
// 	}
// 	return(0);
// }


// if (appended_str[0] != '\0')
// {
// 	free(tokens->str);
// 	tokens->str = ft_strdup(appended_str);
// 	free(appended_str);
// }
// else if (appended_str[0] == '\0')
// {
// 	free(tokens->str);
// 	tokens->str = "";
// }

// int	expander(t_cmd *cmd, t_token *tokens) OLD!!
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	bool	dollar_outside_braces;
// 	char	*str;
// 	char	*expanded_str;
// 	char	*appended_str;
// 	char	*env_key;
// 	char	*env_value;
	
// 	start = 0;
// 	end = 0;
// 	while (tokens != NULL)
// 	{
// 		appended_str = "";
// 		expanded_str = NULL;
// 		i = 0;
// 		str = tokens->str;
// 		while(str && str[i])
// 		{
// 			dollar_outside_braces = true;
// 			if ((((str[i] == '{' && str[i + 1] == '$') || (str[i] == '$')) && not_in_single_quotes(str, i) == true))
// 			{
// 				if (str[i] == '{')
// 				{
// 					dollar_outside_braces = false;
// 					i++;
// 				}
// 				if (dollar_outside_braces == true && str[i + 1] == '{')
// 				{
// 					if (bad_substitution(str, i) == true)
// 					{
// 						printf("Bad substituton.\n"); //FREE?
// 						break ;
// 					}
// 				}
// 				if ((i > 0) && (str[i - 1] == '{'))
// 					start = i - 1;
// 				else
// 					start = i;
// 				i++;
// 				env_key = get_env_key(str, &i);
// 				if (env_key == NULL)
// 				{
// 					raise_error("env_var_name returned NULL");
// 					return (1);
// 				}
// 				env_value = find_env_value(*cmd->data->env, env_key);
// 				if (env_value == NULL)
// 				{
// 					printf("Environment variable not found\n");//!!!
// 					free(env_key);
// 					free(env_value);
// 					if (str[start] == '{')
// 						appended_str = ft_append_char(appended_str, '{');
// 					if ((ft_strlen(str) == 1 && str[start] == '$') || ((ft_strlen(str) >= 3) && str[start] == '{' && str[start + 1] == '$' && str[start + 2] == '}')) 
// 						appended_str = ft_append_char(appended_str, '$'); 
// 					continue ;
// 				}
// 				if ((str[i] == '$') || (str[i] == ' ') || (str[i] == '\0') || (str[i] == '\'') || (str[i] == '\"'))
// 					end = i - 1;
// 				else if (str[i] == '}' || str[i] == '{')
// 				{
// 					end = i;
// 					if (str[i] == '}' && str[start] != '$')
// 						dollar_outside_braces = false;
// 				}
// 				expanded_str = allocate_new_str(str + start, env_value, start, end);
// 				if (dollar_outside_braces == false && str[start] != '$' && str[i] == '}')
// 					expanded_str[ft_strlen(expanded_str)] = '}';
// 				appended_str = ft_strjoin(appended_str, expanded_str);
// 				i = end;
// 				free(expanded_str);
// 				free_cals++;
// 				free(env_key);
// 				free(env_value);
// 				free_cals++;
// 			}
// 			else
// 			{
// 				if (env_value != NULL && ((str[i] == '}' && (str[start] == '{' && str[start + 1] == '$' && curly_braces_closed(str, i) == false))))
// 				{
// 					if (dollar_outside_braces == false)
// 					{
// 						i++;
// 						continue ;
// 					}
// 				}
// 				else if (env_value == NULL && (str[i] == '}' && str[start] == '$' && str[i - 1] != '\"'))
// 				{
// 					i++;
// 					continue ;
// 				}
// 				appended_str = ft_append_char(appended_str, str[i]);
// 			}
// 			i++;
// 		}
// 		if (appended_str[0] != '\0')
// 		{
// 			free(tokens->str);
// 			tokens->str = ft_strdup(appended_str);
// 			free(appended_str);
// 		}
// 		else if (appended_str[0] == '\0')
// 		{
// 			free(tokens->str);
// 			tokens->str = "";
// 		}
// 		tokens = tokens->next;
// 	}
// 	return(0);
// }


// int	expander(t_cmd *cmd, t_token *tokens)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	//bool	dollar_outside_braces;
// 	char	*str;
// 	char	*expanded_str;
// 	char	*appended_str;
// 	char	*env_key;
// 	char	*env_value;
	
// 	start = 0;
// 	end = 0;
// 	while (tokens != NULL)
// 	{
// 		appended_str = "";
// 		expanded_str = NULL;
// 		i = 0;
// 		str = tokens->str;
// 		while(str && str[i])       //-------------
// 		{
// 			if ((str[i] == '$') && not_in_single_quotes(str, i) == true)
// 			{
// 				// if ((i > 0) && (str[i - 1] == '{'))
// 				// 	start = i - 1;
// 				// else
// 					start = i;
// 				i++;
// 				env_key = get_env_key(str, &i);
// 				printf("ENV_KEY: %s\n", env_key);
// 				if (env_key == NULL)
// 				{
// 					raise_error("env_var_name returned NULL");
// 					return (1);
// 				}
// 				env_value = find_env_value(*cmd->data->env, env_key);
// 				if (env_value == NULL)
// 				{
// 					printf("ENV_VALUE: %s\n", env_value);
// 					free(env_key);
// 					free(env_value);
// 					env_value_not_found(&appended_str, str, start); 
// 					continue ;
// 				}
// 				//printf("sssstr[%i] = %c\n", i , str[i]);
// 				if ((str[i] == '$') || (str[i] == ' ') || (str[i] == '\0') || (str[i] == '\'') || (str[i] == '\"'))
// 					end = i - 1;
// 				else if (str[i] == '}' || str[i] == '{')
// 				{

// 					printf("sstr[%i] = %c\n", i , str[i]);
// 					end = i;
// 				}
// 				printf("str_start[%i] = %c\n", start , str[start]);
// 				expanded_str = allocate_new_str(str + start, env_value, start, end);
// 				if (start > 0 && str[start - 1] == '{')
//  					expanded_str[ft_strlen(expanded_str)] = '}';
// 				appended_str = ft_strjoin(appended_str, expanded_str);
// 				printf ("Expanded_str: %s\n", expanded_str);
// 				printf ("Appended_str: %s\n", appended_str);

// 				i = end;
// 				free(expanded_str);
// 				free(env_key);
// 				free(env_value);
// 			}
// 			else
// 			{
// 				// if (((append_check_one(str, env_value, i, start) == false)
// 				// 	&& dollar_outside_braces == false)
// 				// 	|| append_check_two(str, env_value, i, start) == false)
// 				// {
// 				// 	i++;
// 				// 	continue ;
// 				// }
// 				printf("STR[%i] = %c\n", i , str[i]);
// 				appended_str = ft_append_char(appended_str, str[i]);
// 			}
// 			i++;
// 		}                                 //--------------------
// 		if (appended_str[0] != '\0')
// 		{
// 			free(tokens->str);
// 			tokens->str = ft_strdup(appended_str);
// 			free(appended_str);
// 		}
// 		else if (appended_str[0] == '\0')
// 		{
// 			free(tokens->str);
// 			tokens->str = "";
// 		}
// 		tokens = tokens->next;
// 	}
// 	return(0);
// }

int free_cals;
int	malloc_calls;
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
		printf("1str[%i] = %c\n", i , str[i]);
		if (str[i] == '$')
			i++;
		if (str[i] == '{')
			i++;
		while (str[i] && str[i] != '}')
		{
			printf("strrr[%i] = %c\n", i , str[i]);
			if ((ft_strchr(" \"\'~!@$^&*(){[];:|<>,./", str[i]) != 0) && curly_braces_closed(str, i) == false)
				return (true);
			i++;
		}
		printf("2str[%i] = %c\n", i , str[i]);
		if (str[i] == '}')
			i++;
		printf("3str[%i] = %c\n", i , str[i]);

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
		i++;
		printf("4str[%i] = %c\n", i , str[i]);
	}
	return (false);
}


// int	expander_process(t_cmd *cmd, char *str)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	bool	dollar_outside_braces;
// 	char	*expanded_str;
// 	char	*appended_new_str;
// 	char	*env_key;
// 	char	*env_value;

// 	start = 0;
// 	end = 0;
// 	while(str && str[i])       //-------------
// 	{
// 		dollar_outside_braces = true;
// 		if ((((str[i] == '{' && str[i + 1] == '$') || (str[i] == '$'))
// 			&& not_in_single_quotes(str, i) == true))
// 		{
// 			if (str[i] == '{')
// 			{
// 				dollar_outside_braces = false;
// 				i++;
// 			}
// 			if (dollar_outside_braces == true && str[i + 1] == '{')
// 			{
// 				if (bad_substitution(str, i) == true)
// 				{
// 					printf("Bad substituton.\n"); //FREE?
// 					break ;
// 				}
// 			}
// 			if ((i > 0) && (str[i - 1] == '{'))
// 				start = i - 1;
// 			else
// 				start = i;
// 			i++;
// 			env_key = get_env_key(str, &i);
// 			if (env_key == NULL)
// 			{
// 				raise_error("env_var_name returned NULL");
// 				return (1);
// 			}
// 			env_value = find_env_value(*cmd->data->env, env_key);
// 			if (env_value == NULL)
// 			{
// 				printf("Environment variable not found\n");//!!!
// 				free(env_key);
// 				free(env_value);
// 				if (str[start] == '{')
// 					appended_new_str = ft_append_char(appended_new_str, '{');
// 				if ((ft_strlen(str) == 1 && str[start] == '$') || ((ft_strlen(str) >= 3) && str[start] == '{' && str[start + 1] == '$' && str[start +2] == '}')) 
// 					appended_new_str = ft_append_char(appended_new_str, '$'); 
// 				continue ;
// 			}
// 			if ((str[i] == '$') || (str[i] == ' ') || (str[i] == '\0') || (str[i] == '\'') || (str[i] == '\"'))
// 				end = i - 1;
// 			else if (str[i] == '}' || str[i] == '{')
// 			{
// 				end = i;
// 				if (str[i] == '}' && str[start] != '$')
// 					dollar_outside_braces = false;
// 			}
// 			expanded_str = allocate_new_str(str + start, env_value, start, end);
// 			if (dollar_outside_braces == false && str[start] != '$' && str[i] == '}')
// 				expanded_str[ft_strlen(expanded_str)] = '}';
// 			appended_new_str = ft_strjoin(appended_new_str, expanded_str);
// 			i = end;
// 			free(expanded_str);
// 			free(env_key);
// 			free(env_value);
// 		}
// 		else
// 		{
// 			if (env_value != NULL && ((str[i] == '}' && (str[start] == '{' && str[start + 1] == '$' && curly_braces_closed(str, i) == false))))
// 			{
// 				if (dollar_outside_braces == false)
// 				{
// 					i++;
// 					continue ;
// 				}
// 			}
// 			else if (env_value == NULL && (str[i] == '}' && str[start] == '$' && str[i - 1] != '\"'))
// 			{
// 				i++;
// 				continue ;
// 			}
// 			appended_new_str = ft_append_char(appended_new_str, str[i]);
// 		}
// 		i++;
// 	}

// }

static void env_value_not_found(char **appended_new_str, char *str, int start)
{
	printf("Environment variable not found\n");//!!!
	if (str[start] == '{')
		*appended_new_str = ft_append_char(*appended_new_str, '{');
	if ((ft_strlen(str) == 1 && str[start] == '$') || ((ft_strlen(str) >= 3)
		&& str[start] == '{' && str[start + 1] == '$' && str[start + 2] == '}'))
	{
		*appended_new_str = ft_append_char(*appended_new_str, '$');
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

int	expander(t_cmd *cmd, t_token *tokens)
{
	int		i;
	int		start;
	int		end;
	bool	dollar_outside_braces;
	char	*str;
	char	*expanded_str;
	char	*appended_new_str;
	char	*env_key;
	char	*env_value;
	
	start = 0;
	end = 0;
	while (tokens != NULL)
	{
		appended_new_str = "";
		expanded_str = NULL;
		i = 0;
		str = tokens->str;
		while(str && str[i])       //-------------
		{
			dollar_outside_braces = true;
			if ((((str[i] == '{' && str[i + 1] == '$') || (str[i] == '$'))
				&& not_in_single_quotes(str, i) == true))
			{
				if (str[i] == '{')
				{
					dollar_outside_braces = false;
					i++;
				}
				if (dollar_outside_braces == true && str[i + 1] == '{')
				{
					if (bad_substitution(str, i) == true)
					{
						printf("Bad substituton.\n"); //FREE?
						break ;
					}
				}
				if ((i > 0) && (str[i - 1] == '{'))
					start = i - 1;
				else
					start = i;
				i++;
				env_key = get_env_key(str, &i);
				printf("ENV_KEY: %s\n", env_key);
				if (env_key == NULL)
				{
					raise_error("env_var_name returned NULL");
					return (1);
				}
				env_value = find_env_value(*cmd->data->env, env_key);
				if (env_value == NULL)
				{
					printf("ENV_VALUE: %s\n", env_value);
					free(env_key);
					free(env_value);
					env_value_not_found(&appended_new_str, str, start); 
					continue ;
				}
				if ((str[i] == '$') || (str[i] == ' ') || (str[i] == '\0') || (str[i] == '\'') || (str[i] == '\"'))
					end = i - 1;
				else if (str[i] == '}' || str[i] == '{')
				{
					end = i;
					if (str[i] == '}' && str[start] != '$')
						dollar_outside_braces = false;
				}
				expanded_str = allocate_new_str(str + start, env_value, start, end);
				if (dollar_outside_braces == false && str[start] != '$' && str[i] == '}')
					expanded_str[ft_strlen(expanded_str)] = '}';
				appended_new_str = ft_strjoin(appended_new_str, expanded_str);
				i = end;
				free(expanded_str);
				free(env_key);
				free(env_value);
			}
			else
			{
				if (((append_check_one(str, env_value, i, start) == false)
					&& dollar_outside_braces == false)
					|| append_check_two(str, env_value, i, start) == false)
				{
					i++;
					continue ;
				}
				appended_new_str = ft_append_char(appended_new_str, str[i]);
			}
			i++;
		}                                 //--------------------
		if (appended_new_str[0] != '\0')
		{
			free(tokens->str);
			tokens->str = ft_strdup(appended_new_str);
			free(appended_new_str);
		}
		else if (appended_new_str[0] == '\0')
		{
			free(tokens->str);
			tokens->str = "";
		}
		tokens = tokens->next;
	}
	return(0);
}

// int	expander(t_cmd *cmd, t_token *tokens) OLD!!
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	bool	dollar_outside_braces;
// 	char	*str;
// 	char	*expanded_str;
// 	char	*appended_new_str;
// 	char	*env_key;
// 	char	*env_value;
	
// 	start = 0;
// 	end = 0;
// 	while (tokens != NULL)
// 	{
// 		appended_new_str = "";
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
// 						appended_new_str = ft_append_char(appended_new_str, '{');
// 					if ((ft_strlen(str) == 1 && str[start] == '$') || ((ft_strlen(str) >= 3) && str[start] == '{' && str[start + 1] == '$' && str[start + 2] == '}')) 
// 						appended_new_str = ft_append_char(appended_new_str, '$'); 
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
// 				appended_new_str = ft_strjoin(appended_new_str, expanded_str);
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
// 				appended_new_str = ft_append_char(appended_new_str, str[i]);
// 			}
// 			i++;
// 		}
// 		if (appended_new_str[0] != '\0')
// 		{
// 			free(tokens->str);
// 			tokens->str = ft_strdup(appended_new_str);
// 			free(appended_new_str);
// 		}
// 		else if (appended_new_str[0] == '\0')
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
// 	char	*appended_new_str;
// 	char	*env_key;
// 	char	*env_value;
	
// 	start = 0;
// 	end = 0;
// 	while (tokens != NULL)
// 	{
// 		appended_new_str = "";
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
// 					env_value_not_found(&appended_new_str, str, start); 
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
// 				appended_new_str = ft_strjoin(appended_new_str, expanded_str);
// 				printf ("Expanded_str: %s\n", expanded_str);
// 				printf ("Appended_str: %s\n", appended_new_str);

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
// 				appended_new_str = ft_append_char(appended_new_str, str[i]);
// 			}
// 			i++;
// 		}                                 //--------------------
// 		if (appended_new_str[0] != '\0')
// 		{
// 			free(tokens->str);
// 			tokens->str = ft_strdup(appended_new_str);
// 			free(appended_new_str);
// 		}
// 		else if (appended_new_str[0] == '\0')
// 		{
// 			free(tokens->str);
// 			tokens->str = "";
// 		}
// 		tokens = tokens->next;
// 	}
// 	return(0);
// }

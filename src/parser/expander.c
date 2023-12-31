int free_cals;
int	malloc_calls;
#include "../../include/minishell.h"


// static bool curly_braces_closed(char *input, int index)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while(i < index)
// 	{
// 		if (input[i] == '{')
// 			count++;
// 		if (input[i] == '}')
// 			count--;
// 		i++;
// 	}
// 	if (count == 0)
// 		return (true);
// 	return (false);
// }

static char	*get_env_key(char *input, int *i)
{
	int		var_len;
	int		j;
	char	*var_name;

	if (input[*i] == '{')
		(*i)++;
	var_len = 0;
	j = (*i);
	while (input[j] && input[j] != ' ' && input[j] != '\"' && input[j] != '\"' && input[j] != '$' && input[j] != '}' && input[j] != '{')
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
	//(void)cmd;
	
	start = 0;
	end = 0;
	while (tokens != NULL)
	{
		appended_new_str = "";
		expanded_str = NULL;
		i = 0;
		str = tokens->str;
		while(str && str[i])
		{
			dollar_outside_braces = false;
			if ((str[i] == '$') && (not_in_single_quotes(str, i) == true))
			{
				if ((i > 0) && (str[i - 1] == '{'))
					start = i - 1;
				else
					start = i;
				i++;
				if (str[i] != '\0' && str[i] == '{')
					dollar_outside_braces = true;
				env_key = get_env_key(str, &i);
				printf("ENV KEY= %s\n", env_key);
				malloc_calls++;
				if (env_key == NULL)
				{
					raise_error("env_var_name returned NULL");
					return (1);
				}
				env_value = find_env_value(*cmd->data->env, env_key);
				malloc_calls++;
				//printf("iii: %d\n", i);
				if (env_value == NULL)
				{
					printf("Environment variable not found\n");//!!!
					free(env_key);
					free(env_value);
					if (str[0] == '$' || str[0] == '{')
					{
						appended_new_str = "";
						break ;
					}
					else
						continue ;
				}
				if ((str[i] == '$') || (str[i] == ' ') || (str[i] == '\0'))
				{
					end = i - 1;
					printf("start: %d->%c\n", start, str[start]);
					printf("end: %d->%c\n", end, str[end]);
				}
				else if (str[i] == '}' || str[i] == '{')
				{
					end = i;
					printf("start: %d->%c\n", start, str[start]);
					printf("end: %d->%c\n", end, str[end]);
				}
				while (str[i] == '\'' || str[i] == '\"')
				{
					i++;
					end = i;
				}
				expanded_str = allocate_new_str(str + start, env_value, start, end);
				malloc_calls++;
				//printf("i before placing: %d }: %c\n", i, str[end]);
				if (str[end] == '}' && dollar_outside_braces == false)
					expanded_str[ft_strlen(expanded_str)] = '}';
				appended_new_str = ft_strjoin(appended_new_str, expanded_str);
				printf("EXPANDED TOKEN: %s\n", expanded_str);
				printf("APPENDED TOKEN: %s\n", appended_new_str);
				malloc_calls++;
				i = end;
				//printf("i: %d\n", i);
				free(expanded_str);
				free_cals++;
				free(env_key);
				free(env_value);
				free_cals++;
			}
			else if ((str[i] != '{' && str[i] != '}' && str[i] != '\"'))
			{
				//printf("i: %d\n", i);
				//printf("str[%d]: %c\n", i, str[i]);
				appended_new_str = ft_append_char(appended_new_str, str[i]);
			}
			i++;
		}
		if (appended_new_str[0] != '\0')
		{
			free(tokens->str);
			free_cals++;
			tokens->str = ft_strdup(appended_new_str);
			free(appended_new_str);
			free_cals++;
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
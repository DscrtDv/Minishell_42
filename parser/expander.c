
#include "../minishell.h"

// static char	*get_env_var_name(char *input, int *i)
// {
// 	int		var_len;
// 	int		j;
// 	int		x;
// 	char	*var_name;

// 	var_len = 0;
// 	var_name = NULL;
// 	j = (*i);
// 	while (input[j] && input[j] != '$' &&  input[j] != ' ' && input[j] != '\"')
// 	{
// 		var_len++;
// 		j++;
// 	}
// 	printf("var_len = %d\n", var_len);
// 	var_name = malloc(sizeof(char) * var_len + 1);
// 	if (var_name == NULL)
// 		return (NULL);
// 	j = 0;
// 	x = (*i);
// 	while(j < var_len)
// 	{
// 		var_name[j] = input[x];
// 		x++;
// 		j++;
// 	}
// 	return (var_name);
// }

static char	*get_env_var_name(char *input, int *i)
{
	int		var_len;
	int		j;
	//int		x;
	char	*var_name;

	var_len = 0;
	j = (*i);
	while (input[j] && input[j] != '$' &&  input[j] != ' ' && input[j] != '\"')
	{
		var_len++;
		j++;
	}
	//printf("var_len = %d\n", var_len);
	var_name = malloc(sizeof(char) * var_len + 1); // FREE
	if (var_name == NULL)
		return (NULL);
	j = 0;
	//x = (*i);
	while(j < var_len)
	{
		var_name[j] = input[(*i)];
		(*i)++;
		j++;
	}
	return (var_name);
}

// void	expander(t_data *data)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	char	*input;
// 	//char	*input_expanded;
// 	char	*env_var_name;
// 	char	*env_var_value;

// 	i = 0;
// 	start = 0;
// 	end = 0;
// 	input = data->input;
// 	while (input && input[i])
// 	{
// 		if (input[i] == '$' && not_in_single_quotes(input, i) == true)
// 		{
// 			start = i;
// 			i++;
// 			env_var_name = get_env_var_name(input, &i);
// 			printf("i after env_var_name = %d\n", i);
// 			if (env_var_name == NULL)
// 				raise_error("env_var_name returned NULL");
// 			env_var_value = getenv(env_var_name);
// 			if (env_var_value == NULL)
// 				raise_error("Environment variable not found");
// 			//printf("env_var_name= %s\n", env_var_name);
// 			//printf("env_var_value= %s\n", env_var_value);
// 			//i++;
// 			if ((input[i] == '$') || (input[i] == ' ') || (input[i] == '\0'))
// 			{
// 				end = i - 1;
// 				printf("start: %d->%c\n", start, input[start]);
// 				printf("end: %d->%c\n", end, input[end]);

// 				//replace $env with value
// 			}
// 		}
// 		if (input[i] != '$') 
// 			i++;
// 		free(env_var_name);
// 	}
// }

void	expander(t_cmd *cmd, t_token *tokens)
{
	char	*str;
	int		i;
	int		start;
	int		end;
	//char	*input_expanded;
	char	*env_var_name;
	char	*env_var_value;
	(void)cmd;

	i = 0;
	start = 0;
	end = 0;
	while (tokens != NULL)
	{
		str = tokens->str;
		if (str[i] == '$' && not_in_single_quotes(str, i) == true)
		{
			start = i;
			i++;
			env_var_name = get_env_var_name(str, &i);
			//printf("i after env_var_name = %d\n", i);
			if (env_var_name == NULL)
				raise_error("env_var_name returned NULL");
			env_var_value = getenv(env_var_name);
			if (env_var_value == NULL)
				raise_error("Environment variable not found");
			printf("env_var_name= %s\n", env_var_name);
			printf("env_var_value= %s\n", env_var_value);
			//i++;
			if ((str[i] == '$') || (str[i] == ' ') || (str[i] == '\0'))
			{
				end = i - 1;
				printf("start: %d->%c\n", start, str[start]);
				printf("end: %d->%c\n", end, str[end]);

				//replace $env with value
			}
			//if (env_var_name != NULL)
			free(env_var_name);
		}

		if (str[i] != '$') 
			i++;
	
	
		tokens = tokens->next;
	}


}


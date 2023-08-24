
#include "../minishell.h"

static char	*get_env_var_name(char *input, int *i)
{
	int		var_len;
	int		j;
	int		x;
	char	*var_name;

	var_len = 0;
	var_name = NULL;
	j = (*i);
	while (input[j] && input[j] != '$' &&  input[j] != ' ')
	{
		var_len++;
		j++;
	}
	printf("var_len = %d\n", var_len);
	var_name = malloc(sizeof(char) * var_len + 1);
	if (var_name == NULL)
		return (NULL);
	j = 0;
	x = (*i);
	while(j < var_len)
	{
		var_name[j] = input[x];
		x++;
		j++;
	}
	return (var_name);
}

void	expander(t_data *data)
{
	int		i;
	char	*input;
	char	*env_var_name;
	//char	*env_var_pointer;

	i = 0;
	input = data->input;
	while (input && input[i])
	{
		if (input[i] == '$' && not_in_single_quotes(input, i) == true)
		{
			i++;
			// if (input[i] == ' ')
			// 	continue ;
			// printf("\n--->%c is at pos %d\n", data->input[i], i);
			env_var_name = get_env_var_name(input, &i);
			if (env_var_name == NULL)
				raise_error("env_var_name returned NULL");
			printf("env_var_name= %s\n", env_var_name);
		}
		if (input[i] == '$')
			continue ;
		i++;
	}
}
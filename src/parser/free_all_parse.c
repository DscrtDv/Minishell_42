
#include "../../include/minishell.h"

void	free_tokens(t_data *data)
{
	t_token	*temp;
	int	i;

	if (data->commands == NULL)
		return ;
	i = 0;
	while (i < data->n_cmd && data->commands[i].tokens != NULL)
	{
		if (data->commands[i].tokens == NULL)
			break ;
		while (data->commands[i].tokens != NULL)
		{
			temp = data->commands[i].tokens;
			data->commands[i].tokens = data->commands[i].tokens->next;
			if (temp->str != NULL && temp->str[0] != '\0')
			{
				free(temp->str);
				temp->str = NULL;
			}
			free(temp);
			temp = NULL;
		}
		i++;
	}
}

void	_free_array(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_cmds_array(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		free(data->commands[i].name);
		data->commands[i].name = NULL;
		free(data->commands[i].redirections);
		data->commands[i].redirections = NULL;
		_free_array(data->commands[i].redir_files);
		_free_array(data->commands[i].args);
		i++;
	}
	free(data->commands);
	data->commands = NULL;
}

void	free_all_parse(t_data *data)
{
	data->n_hd = 0;
	if (data->input[0] == '\0')
		return ;
	free(data->input);
	data->input = NULL;
	_free_array(data->input_split_by_cmds);
	free_tokens(data);
	if (data->cmd_initialized == true)
		free_cmds_array(data);
	free(data->hd_path);
	data->hd_path = NULL;
}

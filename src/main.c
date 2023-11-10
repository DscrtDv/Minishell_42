
int *g_exit_code;

#include "../include/minishell.h"

void	init_data(t_data *data)
{
	data->cmd_initialized = false;
	data->input = NULL;
	data->n_hd = 0;
	data->input_split_by_cmds = NULL;
	data->commands = NULL;
	data->n_cmd = 1;
	data->hd_path = NULL;
	data->expanded_str_hd = NULL;
}

static	int	set_hd_path(t_data *data)
{
	data->hd_path = getcwd(NULL, 0);
	if (!data->hd_path)
		return (MEM_ERR);
	return (STATUS_OK);
}

static int	parse_input(t_data *data)
{
	if (data->input[0] != '\0')
	{
		if (check_syntax(data) != 0)
		{
			*g_exit_code = 258;
			return (STATUS_KO);
		}
		if (split_by_commands(data) != 0)
		{
			*g_exit_code = 1;
			return (STATUS_KO);
		}
		if (command_builder(data) != 0)
		{
			*g_exit_code = 1;
			return (STATUS_KO);
		}
	}
	return (0);
}

void	main_loop(t_data *data)
{
	while (1)
	{
		init_data(data);
		data->input = readline(RED PROMPT COLOR_RESET "$ " );
		if (data->input == NULL)
			exit_shell(data);
		if (data->input[0] == '\0')
		{
			free(data->input);
			continue ;
		}
		if (data->input[0] != '\0')
			add_history(data->input);
		if (set_hd_path(data) == MEM_ERR)
			malloc_protect(data);
		if (parse_input(data) != 0)
		{
			printf("Error while parsing\n");
			free_all_parse(data);
			continue ;
		}
		if (data->input[0] != '\0')
		  	data->status = init_exec(data);
		free_all_parse(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc > 1)
		raise_error("Program should not have arguments.");
	init_signals(NORMAL);
	data = ft_calloc(sizeof(t_data), 1);
	if (data == NULL)
		return (MEM_ERR);
	init_data(data);
	data->status = 0;
	g_exit_code = &data->status;
	envcpy(data, envp);
	main_loop(data);
	free_data(data, true);
	return(data->status);
}
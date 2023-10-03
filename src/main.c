int	malloc_calls;
int free_cals;
int exit_code;
#include "../include/minishell.h"


void	init_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return ; //!!!!
	data->input = NULL;
	data->input_split_by_cmds = NULL;
	data->commands = NULL;
	data->n_cmd = 1;
}

void	main_loop(t_data *data)
{
	while (1)
	{
		data->n_cmd = 1;	
		data->input_split_by_cmds = NULL;
		data->input = readline(RED PROMPT COLOR_RESET "$ " );
		malloc_calls++;
		if (data->input == NULL)
			exit(EXIT_FAILURE);
		if (data->input[0] != '\0')
			add_history(data->input);
		if (check_syntax(data) != 0)
		{
			update_env(data, "?", ft_itoa(exit_code));
			continue ;
		}
		split_by_commands(data);
		command_builder(data);
		exit_code = init_exec(data);
		update_env(data, "?", ft_itoa(exit_code));
		free_all_parse(data);
		malloc_calls = 0;
		free_cals = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	malloc_calls = 0;
	free_cals = 0;
	exit_code = 0;

	(void)	argv;
	t_data	*data;

	if (argc > 1)
		raise_error("Program should not have arguments.");
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (0);
	init_data(data);
	envcpy(data, envp);
	update_env(data, "?", ft_itoa(exit_code));
	main_loop(data);
	free_data(data);
	return(exit_code);
}

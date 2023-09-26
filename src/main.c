int	malloc_calls;
int free_cals;
#include "../include/minishell.h"


void	init_data(t_data *data)
{
	// data = malloc(sizeof(t_data));
	// if (data == NULL)
	// 	return ; //!!!!
	data->input = NULL;
	data->input_split_by_cmds = NULL;
	data->commands = NULL;
	data->n_cmd = 1;

}

int	main(int argc, char **argv, char **envp)
{
	malloc_calls = 0;
	free_cals = 0;
	(void)	argv;
	t_data	*data;

	if (argc > 1)
		raise_error("Program should not have arguments.");
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (0);
	init_data(data);
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
		check_correct_pipe(data);
		check_correct_redir(data);   
		envcpy(data, envp);
		split_by_commands(data);
		command_builder(data);
		init_exec(data);
		free_all_parse(data);
		malloc_calls = 0;
		free_cals = 0;
	}
	free_data(data);
	return(EXIT_SUCCESS);
}
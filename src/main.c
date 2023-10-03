int	malloc_calls;
int free_cals;
#include "../include/minishell.h"

void	check(void)
{
	system("leaks -q minishell");
}

void	init_data(t_data *data)
{
	// data = malloc(sizeof(t_data));
	// if (data == NULL)
	// 	return ; //!!!!
	data->input = NULL;
	data->input_split_by_cmds = NULL;
	data->commands = NULL;
	data->n_cmd = 0;

}

/* TO FREE:
- tokens structs
- command structs
- input
- input_split_by_cmds
*/  

// static void	print_env(t_data *data)
// {
// 	while(data->env[0])
// 	{
// 		// if(strcmp(data->env[0]->key, "USER")  == 0)
// 		// 	printf("%s\n", data->env[0]->val);
// 		printf("%s = %s\n", data->env[0]->key, data->env[0]->val);
// 		data->env[0] = data->env[0]->next;
// 	}
		
// }

int	main(int argc, char **argv, char **envp)
{
	//atexit(check);
	malloc_calls = 0;
	free_cals = 0;
	(void)	argv;
	t_data	*data;

	if (argc > 1)
		raise_error("Program should not have arguments.");
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (0); //!!!!
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
		// if (check_unclosed_quotes(data) == false)
		// {
		// 	//free_all_parse(data);
		// 	printf("Unclosed quotes detected.\n");
		// 	exit(EXIT_FAILURE);
		// }

		//print_env(data);
		//printf("You entered:%s\n\n", data.input);
		split_by_commands(data);
		//printf("Commands count: %d\n\n", data.cmd_count);
		//print_db_array(&data);
		command_builder(data);
		// if (command_builder(data) == 1) //->not_done !!use return codes!
		// 	printf("Failed to build command!\n");

		// if (data->input != NULL && data->commands != NULL)
		// {
		// 	int i;
		// 	int	j;
		// 	int x;

		// 	i = 0;
		// 	while (i < data->n_cmd)
		// 	{
				
		// 		j = 0;
		// 		printf("\n---Command %d---\n", i);
		// 		printf("Command name: %s\n", data->commands[i].name);
		// 		//printf("Arg1 name: %s\n", data.commands[i].cmd_args[0]);
		// 		while (j < data->commands[i].n_args)
		// 		{
		// 			printf("Arg[%d]: %s\n", j, data->commands[i].args[j]);
		// 			j++;
		// 		}
		// 		x = 0;
		// 		while (x < data->commands[i].n_redir)
		// 		{
		// 			printf("Redir type[%d]: %d\n", x, data->commands[i].redirections[x]);
		// 			printf("Redir file[%d]: %s\n", x, data->commands[i].redir_files[x]);
		// 			x++;
		// 		}

		// 		i++;
		// 	}
		// }
		init_exec(data);
		//-remove outter quotes
		//-redirections/heredocs
		//-signals
		free_all_parse(data);
		//rl_cleanup_after_signal();
		//printf("MALLOC CALLS---> %d\n", malloc_calls);
		//printf("FREE CALLS---> %d\n", free_cals);
		malloc_calls = 0;
		free_cals = 0;

	}
	free(data);
	return(EXIT_SUCCESS);
}

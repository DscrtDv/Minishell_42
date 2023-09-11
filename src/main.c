
#include"../include/minishell.h"

int		exit_code;

void	check(void)
{
	system("leaks -q minishell");
}

void	init_data(t_data *data)
{
	data->input = NULL;
	data->input_split_by_cmds = NULL;
	data->cmd_count = 1;
}

/* TO FREE:
- tokens structs
- command structs
- input
- input_split_by_cmds
*/  

int	main(int argc, char **argv, char **envp)
{
	(void)	argv;
	t_data	data;

	//atexit(check);
	if (argc > 1)
		raise_error("Program should not have arguments.");
	
	init_data(&data);
	envcpy(&data, envp);
	while (1)
	{
		data.cmd_count = 1;
		//run_command_test();	
		data.input_split_by_cmds = NULL;
		data.input = readline(RED PROMPT COLOR_RESET "$ ");
		if (data.input == NULL)
			exit(EXIT_FAILURE);
		check_correct_pipe(&data);
		check_correct_redir(&data);   
		//check_unclosed_quotes(&data);
		
		//expander(&data); // --> not done, perform it after tokenization!!!

		//printf("You entered:%s\n\n", data.input);
		split_by_commands(&data);
		//printf("Commands count: %d\n\n", data.cmd_count);
		//print_db_array(&data);
		command_builder(&data); //->not_done

		if (data.input != NULL)
		{
			int i;
			int	j;

			i = 0;
			while (i < data.cmd_count)
			{
				j = 0;
				printf("Command(%d) name: %s\n", i, data.commands[i].cmd_name);
				//printf("Arg1 name: %s\n", data.commands[i].cmd_args[0]);
				//while (data.commands[i])
				while (j < data.commands[i].cmd_args_count)
				{
					printf("Arg[%d]: %s\n", j, data.commands[i].cmd_args[j]);
					j++;
				}
				i++;
			}
			i = 0;
		}
		printf("-------------------exec----------------------\n");
		//-remove outter quotes
		//-redirections/heredocs
		//-signals
		exit_code = init_exec(&data, envp);
		//printf("PWD: %s | OLDPWD: %s \n", ft_getenv(&data, "PWD"), ft_getenv(&data, "OLDPWD"));
		free_data(&data);
	}
	return(exit_code);
}
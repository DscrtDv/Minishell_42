
#include"../include/minishell.h"

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
	(void)	envp;
	t_data	data;

	//atexit(check);
	if (argc > 1)
		raise_error("Program should not have arguments.");
	
	init_data(&data);
	while (1)
	{
		data.cmd_count = 1;
		//run_command_test();	
		data.input_split_by_cmds = NULL;
		data.input = readline(PROMPT);
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
			while (data.env[i])
			{
				printf("%s\n",data.env[i]);
				i++;
			}
		}
		printf("-------------------exec----------------------\n");
		//-remove outter quotes
		//-redirections/heredocs
		//-signals
		init_exec(&data);
		free_all_parse(&data);
	}
	return(EXIT_SUCCESS);
}




// void	run_command_test(char **envp)
// {
// 	//int		pid;
// 	//int		child_status;
// 	char *cmd_name = "wc";
// 	char *cmd_args[] = { "wc", "-l", NULL };

// 	execve(cmd_name, cmd_args, envp);
// 	// will reach the following line only if execve fails, otherwise execve will terminate the current process, so it must be called from a child process!
// 	//raise_error("_execve function failed running the command");

	
// 	// pid = fork();
// 	// if (pid == -1)
// 	// 	raise_error ("Error while creating the child process");
// 	// if (pid == 0)
// 	// {
// 	// 	execve("ls", cmd_args, env);
// 	// 	raise_error("execve function failed running the command");
		
// 	// }
// 	// // else
// 	// // 	//wait(NULL);
// 	// // 	waitpid(0, &child_status, 0);
// 	// if (pid != 0)
// 	// 	wait(NULL);
// }
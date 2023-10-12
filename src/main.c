int	malloc_calls;
int free_cals;
int exit_code;
#include "../include/minishell.h"

void	check(void)
{
	system("leaks -q minishell");
}

void	init_data(t_data *data)
{
	data->input = NULL;
	data->input_split_by_cmds = NULL;
	data->commands = NULL;
	data->envp = NULL;
	data->n_cmd = 1;
}

void	main_loop(t_data *data)
{
	while (1)
	{
		data->n_cmd = 1;	
		data->input_split_by_cmds = NULL;
		data->input = readline(RED PROMPT COLOR_RESET "$ " );
		if (data->input == NULL)
			exit(EXIT_FAILURE);
		if (data->input[0] != '\0')
			add_history(data->input);
		if (check_syntax(data) != 0)
		{
			update_env(data, "?", ft_itoa(exit_code));
			//free
			continue ;
		}
		if (split_by_commands(data) != 0)
		{
			update_env(data, "?", ft_itoa(1));
			//free
			continue ;
		}
		if (command_builder(data) == 1) //->not_done !!use return codes!
			continue ;
		if (data->input[0] != '\0')
		 	exit_code = init_exec(data);
		update_env(data, "?", ft_itoa(exit_code));
		free_all_parse(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	//atexit(check);
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


		//-->LEAVE THIS ONE HERE FOR NOW, I USE IT TO TEST MY PARSER <--

		// if (data && data->input[0] != '\0' && data->commands != NULL)
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

int exit_code;
#include "../include/minishell.h"

void	init_data(t_data *data)
{
	data->cmd_initialized = false;
	data->input = NULL;
	data->n_hd = 0;
	data->input_split_by_cmds = NULL;
	data->commands = NULL;
	data->n_cmd = 1;
}

static int parse_input(t_data *data)
{
	if (data->input[0] != '\0')
	{	
		if (check_syntax(data) != 0)  //-> malloc  protected
		{
			update_env(data, "?", ft_itoa(exit_code));
			return (1);
		}
		if (split_by_commands(data) != 0) //-> malloc protected
		{
			update_env(data, "?", ft_itoa(1));
			return (1);
		}
		if (command_builder(data) != 0)
		{
			printf("Failed to build command!\n");
			update_env(data, "?", ft_itoa(1));
			return (1);
		}
		if (handle_hd(data) == -1)
		{
			update_env(data, "?", ft_itoa(1));
			return (1);
		}
	}
	return (0);
}

void	main_loop(t_data *data, char **envp)
{
	char *status;
	while (1)
	{
		init_data(data);
		data->hd_path = getcwd(NULL, 0);
		if (!data->hd_path)
			malloc_protect(data);
		data->input = readline(RED PROMPT COLOR_RESET "$ " );
		if (data->input == NULL)
		{
			free(data->hd_path);
			exit(EXIT_FAILURE);
		}
		if (data->input[0] == '\0')
		{
			free(data->hd_path);
			free(data->input);
			continue ;
		}
		if (data->input[0] != '\0')
			add_history(data->input);
		if (parse_input(data) != 0)
		{
			printf("Error while parsing\n");
			free_all_parse(data);
			continue ;
		}
		if (data->input[0] != '\0')
		  	exit_code = init_exec(data, envp);
		clean_hds(data);
		status = ft_itoa(exit_code);
		if (!status)
			exit (MEM_ERR);
		update_env(data, "?", status);
		free(status);
		free(data->hd_path);
		free_all_parse(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	exit_code = 0;
	char	*status;
	(void)	argv;
	t_data	*data;

	if (argc > 1)
		raise_error("Program should not have arguments.");
	init_signals(NORMAL);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (MEM_ERR);
	init_data(data);
	envcpy(data, envp);
	status = ft_itoa(exit_code);
	if (!status)
		exit(MEM_ERR);
	update_env(data, "?", status);
	free(status);
	main_loop(data, envp);
	free_data(data);
	//free(data);
	return(exit_code);
}


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
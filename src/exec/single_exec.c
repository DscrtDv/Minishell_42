/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_exec.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:01:31 by tim           #+#    #+#                 */
/*   Updated: 2023/11/08 14:01:33 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*paths_loop(t_data *data, char **paths, char *name)
{
	int		i;
	char	*bin_path;

	i = 0;
	while (paths[i])
	{
		if (!ft_strcmp(paths[i], "/bin") || !ft_strcmp(paths[i], "/usr/bin"))
		{
			bin_path = path_join(paths[i], "/", name);
			if (!bin_path)
				return (ft_free_array(paths), malloc_protect(data), NULL);
			if (access_check(bin_path))
				return (bin_path);
			free(bin_path);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(t_data *data, char *name)
{
	char	**paths;
	char	*full_path;
	char	*bin_path;

	full_path = ft_getenv(data, "PATH");
	if (!full_path)
		return (NULL);
	if (!is_splitable(full_path))
		return (single_path(full_path, name));
	paths = ft_split(full_path, ':');
	if (!paths)
		return (malloc_protect(data), NULL);
	bin_path = paths_loop(data, paths, name);
	return (ft_free_array(paths), bin_path);
}

int	exec_simple(t_data *data)
{
	t_builtin	f_builtin;

	if (!data->commands[0].name)
		return (redir_type(data, 0), EXIT_SUCCESS);
	f_builtin = is_builtin(data->commands[0].name);
	if (f_builtin)
		return (exec_builtin(data, 0, f_builtin));
	else
		return (exec_bin(data));
	return (1);
}

void	exec_single(t_data *data)
{
	t_cmd	*cmd;
	char	*path;
	char	*name;

	data->status = 0;
	exec_redir(data, 0);
	cmd = &(data->commands[0]);
	name = data->commands[0].name;
	if (name[0] == '\0')
		exit(data->status);
	path = get_path(data, name);
	if (!path)
		path = name;
	execve(path, cmd->args, data->envp);
	data->status = set_error(name);
	free_data(data);
	exit(data->status);
}

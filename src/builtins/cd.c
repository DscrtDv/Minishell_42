#include "../../include/minishell.h"

static int	cd_check(t_cmd *cmd)
{
	if (cmd->n_args > 2)
	{
		error_msg("cd", "too many arguments", NULL);
		return (STATUS_KO);
	}
	return (STATUS_OK);
}

static int	chdir_check(t_data *data, char *path, char *curdir)
{
	char	*new_dir;

	new_dir = getcwd(NULL, 0);
	if (!new_dir)
		return (malloc_protect(data), MEM_ERR);
	if (!ft_strcmp(path, new_dir))
		return (free(new_dir), EXIT_SUCCESS);
	if (chdir(path))
	{
		error_msg("cd", path, "No such file or directory");
		return (free(new_dir), STATUS_KO);
	}
	update_env(data, "OLDPWD", curdir);
	update_env(data, "PWD", new_dir);
	return (STATUS_OK);
}

static int	cd_home(t_data *data, char *curdir)
{
	char	*path;

	path = ft_getenv(data, "HOME");
	if (!path)
	{
		error_msg("cd", "HOME not set", NULL);
		return (STATUS_KO);
	}
	return (chdir_check(data, path, curdir));
}

int	f_cd(t_data *data, int index)
{
	char	curdir[MAXPATHLEN];
	char	*path;
	char	*oldpwd;
	t_cmd	*cmd;

	getcwd(curdir, MAXPATHLEN);
	oldpwd = ft_getenv(data, "OLDPWD");
	cmd = &(data->commands[index]);
	if (cd_check(cmd) == STATUS_KO)
		return (STATUS_KO);
	if (cmd->n_args == 1 || !ft_strcmp(cmd->args[1], "~"))
		return (cd_home(data, curdir));
	else
		path = cmd->args[1];
	if (!ft_strcmp(path, "-"))
	{
		if (!oldpwd)
		{
			error_msg("cd", "OLDPWD not set", NULL);
			return (STATUS_KO);
		}
		path = oldpwd;
	}
	return (chdir_check(data, path, curdir));
}

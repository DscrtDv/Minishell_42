
#include "../../include/minishell.h"

int move_index(char *str, int index, int index_r)
{
	int	i;

	i = index;
	if (str[i] != '\'' && str[i] != '\"')
		i++;
	else
		i = index_r + 1;
	return (i);
}

int remove_outer_quotes_redir(t_cmd *cmd)
{
	char 	*clean_str;
	char	*new_str;
	int		i;
	bool	only_quotes;

	i = 0;
	if (cmd->redir_files == NULL)
		return (0);
	while (cmd->redir_files[i] != NULL)
	{
		new_str = "";
		clean_str = NULL;
		if (remove_quotes_loop(cmd->redir_files[i], &clean_str,
				&new_str, &only_quotes) != 0)
			return (1);
		free(cmd->redir_files[i]);
		cmd->redir_files[i] = ft_strdup(new_str);
		if (cmd->redir_files[i] == NULL)
			return (free(new_str), 1);
		if (new_str[0] != '\0')
			free(new_str);
		i++;
	}
	return (0);
}

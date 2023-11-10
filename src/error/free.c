/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:00:55 by tim           #+#    #+#                 */
/*   Updated: 2023/11/10 16:01:19 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	free_node(t_env *node)
{
	free(node->key);
	free(node->val);
	free(node);
	return (EXIT_SUCCESS);
}

int	free_list(t_env **env)
{
	t_env	*node;
	t_env	*temp;

	node = *env;
	while (node)
	{
		temp = node;
		node = node->next;
		free_node(temp);
	}
	free(env);
	return (EXIT_SUCCESS);
}

int	free_data(t_data *data, bool free_data)
{
	if (data->input)
		free(data->input);
	if (data->input_split_by_cmds)
	{
		ft_free_array(data->input_split_by_cmds);
	}
	free_tokens(data);
	if (data->env)
		free_list(data->env);
	if (data->envp)
		ft_free_array(data->envp);
	if (data->cmd_initialized)
		free_cmds_array(data);
	if (data->hd_path)
		free(data->hd_path);
	if (free_data && data != NULL)
		free(data);	
	set_null(data, free_data);
	return (EXIT_SUCCESS);
}

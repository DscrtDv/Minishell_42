
#include "../../include/minishell.h"

void init_quotes_indexes(int *i, int *index_l, int *index_r)
{
	*index_l = 0;
	*index_r = 0;
	*index_l = *i;
	(*i)++;
}

static void skip_consec_quotes(char *str, int *i)
{
	if ((str[*i] == '\'' && str[*i + 1] == '\'')
			|| (str[*i] == '\"' && str[*i + 1] == '\"'))
	{
		while (str[*i] && (str[*i] == '\'' || str[*i] == '\"'))
			(*i)++;
	}
}

int remove_quotes_loop(char *str, char **clean_str, char **new_str, bool *only_quotes)
{
	int		i;
	int		index_r;

	i = 0;
	index_r = 0;
	*only_quotes = false;
	while (str && str[i])
	{
		skip_consec_quotes(str, &i);
		if (str[i] == '\0')
		{
			*only_quotes = true; 
			break ;
		}
		index_r = remove_quote_selector(str, clean_str, new_str, &i);
		if (index_r == -1)
			return (1);
		else if (index_r == -2)
		{
			*only_quotes = true;
			return (0);
		}
		i = move_index(str, i, index_r);
	}
	return (0);
}

int remove_outer_quotes(t_token *tokens)
{
	char 	*clean_str;
	char	*new_str;
	char	*str;
	bool	only_quotes;

	while (tokens != NULL)
	{
		str = tokens->str;
		new_str = "";
		clean_str = NULL;
		if (remove_quotes_loop(str, &clean_str, &new_str, &only_quotes) != 0)
			return (1);
		if (tokens->str[0] != '\0')
			free(tokens->str);
		if (only_quotes == true)
			tokens->str = "";
		else if (new_str[0] != '\0')
		{
			tokens->str = ft_strdup(new_str);
			if (tokens->str == NULL)
			{
				free(new_str);
				return (1);
			}
		}
		if (new_str[0] != '\0')
			free(new_str);
		tokens = tokens->next;
	}
	return (0);
}

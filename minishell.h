
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

extern int	malloc_calls;
extern int free_cals;

//-------ENUM STRUCTS-------//

// typedef enum s_id_token
// {
// 	DOLLAR,
// 	WORD,
// }			t_id_token;

typedef enum s_redir_type
{
	IN_SINGLE,
	IN_DOUBLE,
	OUT_SINGLE,
	OUT_DOUBLE,
	
}			t_redir_type;

//-------STRUCT-------//

// typedef struct s_redir_data
// {
// 	int				type;
// 	char			*

// }			t_redir_data;

typedef struct	s_env
{
	char			*val;
	char			*key;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*str; //FREE
	int				type;
	
	struct s_token	*next; //FREE
	
}					t_token;


typedef struct s_cmd
{
	int				redir_count;
	int				cmd_args_count;
	char			*cmd_name; //FREE
	char			**cmd_args; //FREE
	char			**redir_files; //FREE
	char			*here_doc_delim;
	t_redir_type 	*redirections; //FREE
	t_token			*cmd_tokens; //FREE	
	struct s_data	*data;
}				t_cmd;

typedef struct s_data
{
	int				cmd_count;
	char			*input; //FREE
	char			**input_split_by_cmds; //FREE
	t_env			**env;
	t_cmd			*commands; //FREE	
}					t_data;


//-------UTILS-------//

void 				raise_error(char *str);
void 				raise_error_free(char *str, t_data *data);
void				print_prompt(void);
void				init_data(t_data *data);
void				free_all_parse(t_data *data);
void				get_cmd_count(t_data *data);
void				split_lefmost_cmd(t_data *data, char *input, int i, int *j);
void				split_into_cmds(t_data *data, char *input, int i, int *j);
bool				check_quotes(char *input, char c, int current_pos);



//-------UTILS LISTS-------//

t_token				*create_token(char *word);
void 				insert_at_end(t_token **lst, t_token *new);


//-------SYNTAX-------//

void				check_correct_pipe(t_data *data);
void				check_correct_redir(t_data *data);
void				check_unclosed_quotes(t_data *data);


//-------LEXER-------//

void				split_by_pipes(t_data *data);
int					get_end_token_index(char *input, int i);
char				*isolate_token(char *command, int i);
char				*_isolate_token(char *input, int start, int end);
char 				*isolate_redir(char *command, char c, int *i, char *word);
void				split_by_commands(t_data *data);
void				split_by_delimiters(t_data *data);
bool				not_in_quotes(char *input, int current_pos);
bool				not_in_single_quotes(char *input, int current_pos);
int					skip_quotes(char *input, char c, int i);
int 				command_builder(t_data *data);


//-------EXPANDER-------//

int					expander(t_cmd *cmd, t_token *token);

//-------TIM-------//

void    			envcpy(t_data *data, char **envp);
int     			find_equal(char *str);
t_env   			*create_node(t_data *data, char *envp, int pos);

#endif
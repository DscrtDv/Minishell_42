
#ifndef MINISHELL_H
# define MINISHELL_H

# include"libft/libft.h"
# include<readline/readline.h>
# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<string.h>
# include<stdbool.h>

//-------ENUM-------//

// typedef enum s_id_token
// {
// 	DOLLAR,
// 	SPACE,
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

typedef struct s_token
{
	char			*str;
	int				type;
	
	struct s_token	*next;
	
}					t_token;

typedef struct s_cmd
{
	char			*cmd_name;
	char			**cmd_args;
	//int				
	t_redir_type 	*redirections;
	struct s_cmd	*next; 
	
}					t_cmd;

typedef struct s_data
{
	int				cmd_count;
	char			*input;
	char			**input_split_by_cmds;
	char			**env;
	
	t_cmd			*cmd_list;
	t_token			*token_list;
	
}					t_data;


//-------UTILS PROTOTYPES-------//

void 				raise_error(char *str);
void 				raise_error_free(char *str, t_data *data);
void				print_prompt(void);
void				init_data(t_data *data);
void				free_all_parse(t_data *data);
void				get_cmd_count(t_data *data);
void				split_lefmost_cmd(t_data *data, char *input, int i, int *j);

void				split_into_cmds(t_data *data, char *input, int i, int *j);



//-------SYNTAX PROTOTYPES-------//

void				check_correct_pipe(t_data *data);
void				check_correct_redir(t_data *data);

//-------LEXER PROTOTYPES-------//

void				split_by_pipes(t_data *data);
int					get_end_token_index(char *input, int i);
char				*isolate_token(char *command, int i);
char				*_isolate_token(char *input, int start, int end);
char 				*isolate_redir(char *command, char c, int *i, char *word);

void				split_by_commands(t_data *data);
void				split_by_delimiters(t_data *data);
int					not_in_quotes(char *input, int current_pos);
int					skip_quotes(char *input, char c, int i);
void 				command_builder(t_data *data);


#endif
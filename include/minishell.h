#ifndef MINISHELL_H
# define MINISHELL_H
# define RED 			"\e[1;31m"
# define COLOR_RESET 	"\e[0m"
# define PROMPT 		"BloodySHELL"
# define READ 			0
# define WRITE 			1
# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdint.h>

extern int		exit_code;
extern int		malloc_calls;
extern int 		free_cals;
//-------ENUM STRUCTS-------//

typedef enum s_id_token
{
	DOLLAR,
	_SPACE,
	WORD,
}			t_id_token;

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

typedef struct	s_env
{
	char			*val;
	char			*key;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd
{
	int				n_redir;
	int				n_args;
	char			*name; //FREE
	char			**args; //FREE
	char			**redir_files; //FREE
	char			*here_doc_delim;
	t_redir_type 	*redirections; //FREE
	t_token			*tokens; //FREE
	int32_t			fd_in;
	int32_t			fd_out;
	struct s_data	*data;
}				t_cmd;

typedef struct s_data
{
	int				n_cmd;
	char			*input;
	char			**input_split_by_cmds;
	t_env			**env;
	t_cmd			*commands;
	int				pipe[2];
	pid_t			pid;
	int				status;
}					t_data;

extern int		exit_code;
//-------EXEC---------//
typedef	int		(*t_builtin)();
int 	init_exec(t_data *data);
void    exec_single(t_data *data);

//redir
void	exec_redir(t_data *data, int index);

//builtins
int 	f_echo(t_data *data);
int		f_pwd(t_data *data);
int		f_cd(t_data *data);
int     f_env(t_data *data);
int     f_export(t_data *data);
int		f_unset(t_data *data);

//utils
int 	ft_strcmp(const char *s1, const char *s2);

//env
void    envcpy(t_data *data, char **envp);
int     find_equal(char *str);
t_env   *create_node(t_data *data, char *envp, int pos);
char    *ft_getenv(t_data *data, char *key);
void    update_env(t_data *data, char *key, char *str);
int     pop(t_data *data, char *key);

//Free
int		free_node(t_env *node);
int		free_list(t_env **env);
int		free_cmd_struct(t_cmd *cmd);
int		free_cmds(t_data *data);
int		free_data(t_data *data);
//void     free_tokens(t_data *data);

//error
void	malloc_protect(t_data *data);
void    error_msg(char *str);

//-------UTILS-------//

void 				raise_error(char *str);
void 				raise_error_free(char *str, t_data *data);
void				print_prompt(void);
void				init_data(t_data *data);
void				free_all_parse(t_data *data);
void				get_n_cmd(t_data *data);
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

int					expander(t_cmd *cmd, t_token *tokens);

#endif
#ifndef MINISHELL_H
# define MINISHELL_H
# define RED 			"\e[1;31m"
# define COLOR_RESET 	"\e[0m"
# define PROMPT 		"BloodySHELL"
# define READ 			0
# define WRITE 			1
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
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

// typedef enum s_status
// {
// 	STATUS_OK;
// 	MEM_ERROR;
// 	SYNTAX_ERROR;


// }

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
	int				pipe_fd[2];
	pid_t			pid;
	int				status;
}					t_data;

typedef struct s_exp_data
{
	int		start;
	int		end;
	int		valid_expansion;
	bool	dollar_out;
	char	*expanded_str;
	char	*appended_str;
	char	*env_key;
	char	*env_value;
	struct s_data	*data;

}					t_exp_data;

extern int		exit_code;
//-------EXEC---------//
typedef	int		(*t_builtin)();
int 	init_exec(t_data *data);
void    exec_single(t_data *data);
char    *get_path(t_data *data, char *name);
int  	init_pipes(t_data *data, int prev_fd, int index);
t_builtin is_builtin(char *name);
int     exec_builtin(t_data *data, int index, t_builtin f_builtin);

//redir
void	exec_redir(t_data *data, int index);
int     redir_type(t_data *data, int index);
bool    redir_check(t_cmd *cmd);
int     redir_in(t_data *data, int index);
int     redir_out(t_data *data, int index);
int     set_fds(t_data *data, int index);

//builtins
int 	f_echo(t_data *data, int index);
int		f_pwd(t_data *data, int index);
int		f_cd(t_data *data, int index);
int     f_env(t_data *data, int index);
int     f_export(t_data *data, int index);
int		f_unset(t_data *data, int index);
int    	f_exit(t_data *data, int index);
void    print_env(t_data *data, int index);

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
int     set_error();

//-------UTILS-------//

void 				raise_error(char *str);
void 				raise_error_free(char *str, t_data *data);
void				print_prompt(void);
void				init_data(t_data *data);
void				free_all_parse(t_data *data);
void				get_n_cmd(t_data *data);
int					split_lefmost_cmd(t_data *data, char *input, int i, int *j);
int					split_into_cmds(t_data *data, char *input, int i, int *j);
bool				check_quotes(char *input, char c, int current_pos);
bool				_check_quotes(char *input, char c, int current_pos);



//-------UTILS LISTS-------//

t_token				*create_token(char *word);
void 				insert_at_end(t_token **lst, t_token *new);
char				*ft_append_char(char *str, char c);


//-------SYNTAX-------//

bool				correct_pipes(t_data *data);
bool				correct_redir(t_data *data);
bool				closed_quotes(t_data *data);
bool				check_single_quotes(char *input, size_t current_pos);
bool				check_double_quotes(char *input, size_t current_pos);
int					check_syntax(t_data *data);



//-------LEXER-------//

void				split_by_pipes(t_data *data);
int					get_end_token_index(char *input, int i);
char				*isolate_token(char *command, int i);
char				*_isolate_token(char *input, int start, int end);
char 				*isolate_redir(char *command, char c, int *i, char *word);
int					split_by_commands(t_data *data);
void				split_by_delimiters(t_data *data);
bool				not_in_quotes(char *input, int current_pos);
bool				not_in_single_quotes(char *input, int current_pos);
int					skip_quotes(char *input, char c, int i);
int 				command_builder(t_data *data);


//-------EXPANDER-------//

int					expander(t_cmd *cmd, t_data *data);

#endif
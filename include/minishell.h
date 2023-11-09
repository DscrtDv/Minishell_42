/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tim <tim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:26:32 by tim           #+#    #+#                 */
/*   Updated: 2023/11/09 10:31:26 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RED 			"\e[1;31m"
# define COLOR_RESET 	"\e[0m"
# define PROMPT 		"BloodySHELL"
# define READ 			0
# define WRITE 			1
# define STATUS_OK		0
# define STATUS_KO		1
# define MEM_ERR		137
# define PERM_DENIED	126
# define NOT_FOUND		127
# include "../libft/includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int			g_exit_code;
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

typedef enum s_signal_modes
{
	NORMAL,
	PARENT,
	CHILD,
	HEREDOC,
}			t_signal_modes;

typedef struct s_token
{
	char			*str;
	int				type;	
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*val;
	char			*key;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd
{
	int				n_redir;
	int				n_args;
	char			*name;
	char			**args;
	char			**redir_files;
	t_redir_type	*redirections;
	t_token			*tokens;
	int32_t			fd_in;
	int32_t			fd_out;
	bool			has_hd;
	struct s_data	*data;
}				t_cmd;

typedef struct s_data
{
	bool			cmd_initialized;
	int				n_cmd;
	char			*input;
	char			**input_split_by_cmds;
	t_env			**env;
	char			**envp;
	t_cmd			*commands;
	int				pipe_fd[2];
	pid_t			pid;
	int				status;
	char			*hd_path;
	char			*expanded_str_hd;
	int				n_hd;
}					t_data;

typedef struct s_exp_data
{
	int				start;
	int				end;
	int				valid_expansion;
	bool			mem_error;
	bool			dollar_out;
	char			*expanded_str;
	char			*appended_str;
	char			*env_key;
	char			*env_value;
	struct s_data	*data;

}					t_exp_data;

//-------EXEC---------//
typedef int			(*t_builtin)();
void				exec_single(t_data *data);
int					exec_simple(t_data *data);
int					exec_multiple(t_data *data);
int					exec_bin(t_data *data);
int					exec_builtin(t_data *data, int index, t_builtin f_builtin);
void				exec_child(t_data *data, int fd_in, int index);
int					init_exec(t_data *data);
int					init_pipes(t_data *data, int prev_fd, int index);
t_builtin			is_builtin(char *name);
int					builtin_child(t_builtin f_builtin, t_data *data, int index);

//------PATHS---------//
char				*get_path(t_data *data, char *name);
char				*path_join(char *dest, char *src1, char *src2);
bool				access_check(char *path);
bool				path_check(char *path);
bool				is_splitable(char *path);
char				*single_path(char *path, char *name);

//redir
void				exec_redir(t_data *data, int index);
int					redir_type(t_data *data, int index);
bool				redir_check(t_cmd *cmd);
int					redir_in(t_data *data, int index);
int					redir_out(t_data *data, int index);
int					set_fds(t_data *data, int index);
char				*err_redir(void);

//builtins
int					f_echo(t_data *data, int index);
int					f_pwd(t_data *data, int index);
int					f_cd(t_data *data, int index);
int					f_env(t_data *data, int index);
int					f_export(t_data *data, int index);
int					f_unset(t_data *data, int index);
int					f_exit(t_data *data, int index);
void				print_env(t_data *data, int index, bool is_env);

//utils
int					ft_strcmp(const char *s1, const char *s2);

//env
void				envcpy(t_data *data, char **envp);
int					find_equal(char *str);
t_env				*new_node(char *key, char *val);
t_env				*create_node(t_data *data, char *envp, int pos);
char				*ft_getenv(t_data *data, char *key);
int					update_env(t_data *data, char *key, char *str);
int					pop(t_data *data, char *key);

//hd
int					set_delims(t_cmd *cmd, int size);
int					create_filename(t_cmd *cmd, int n_hd, int index);
int					fork_hd(t_cmd *cmd, int hd_index, char **delims);
int					handle_hd(t_data *data);
void				clean_hds(t_data *data);
int32_t				hd_write(t_cmd *cmd, int hd_index, char **delims);

//Free
int					free_node(t_env *node);
int					free_list(t_env **env);
int					free_data(t_data *data);
void				set_null(t_data *data);
void				free_tokens(t_data *data);
void				free_cmds_array(t_data *data);
void				_free_array(char **array);


//error
void				malloc_protect(t_data *data);
void				error_msg(char *func, char *s1, char *s2);
int					set_error(char *name);

//----------PARSING----------//

//-------UTILS-------//

void				raise_error(char *str);
void				print_prompt(void);
void				init_data(t_data *data);
void				free_all_parse(t_data *data);
void				get_n_cmd(t_data *data);
int					split_lefmost_cmd(t_data *data, char *input, int i, int *j);
int					split_into_cmds(t_data *data, char *input, int i, int *j);
bool				check_quotes(char *input, char c, int current_pos);
char				*ft_join(char *s1, char const *s2);

//-------UTILS LISTS-------//

t_token				*create_token(char *word);
void				insert_at_end(t_token **lst, t_token *new);
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
char				*isolate_redir(char *command, char c, int *i, char *word);
int					split_by_commands(t_data *data);
void				split_by_delimiters(t_data *data);
bool				not_in_quotes(char *input, int current_pos);
bool				not_in_single_quotes(char *input, int current_pos);
int					skip_quotes(char *input, char c, int i);
int					command_builder(t_data *data);
int					remove_outer_quotes(t_token *tokens);

void				initialize_exp_data(t_exp_data *exp, t_data *data, int *i);
void				set_start(t_exp_data *exp, char *str, int *i);
void				set_end(t_exp_data *exp, char *str, int *i);
void				env_value_not_found(t_exp_data *exp, char *str, int i);
int					valid_expansion(t_exp_data *exp, \
									t_data *data, char *str, int *i);
bool				curly_braces_closed(char *input, int index);
int					append_check(t_exp_data *exp, char *str, int i);
char				*allocate_new_str(char *str, char *value, \
									int start, int end);
int					remove_quote_selector(char *str, char **clean_str, \
									char **new_str, int *i);
int					move_index(char *str, int index, int index_r);
void				init_quotes_indexes(int *i, int *index_l, int *index_r);
int					remove_quotes_loop(char *str, char **clean_str, \
										char **new_str, bool *only_quotes);
t_token				*tokenize(char *command, int i, t_token *tokens);
void				set_redirections_type(t_cmd *cmd, t_token *tokens);
t_cmd				*configure_redirections(t_cmd *cmd, t_token *tokens);
int					remove_outer_quotes_redir(t_cmd *cmd);
t_token				*save_redir(t_token **tokens, char *command, int *i);
int					_lstsize(t_token *lst);
int					init_cmd_array(t_data *data);
int					n_args(t_token *tokens);
void				set_start_env_key(char *input, \
									int *i, int *j, int *var_len);
bool				correct_dollar(t_data *data);
int					append_helper(t_exp_data *exp, char *str, int *i);
bool				no_quote(char *input, int current_pos);
void				init_signals(t_signal_modes mode);
// void				init_signals(t_signal_modes mode, t_data *data);

//-------EXPANDER-------//

int					expander(t_cmd *cmd, t_data *data);
char				*expand_heredoc_line(char *str, t_data *data);

#endif
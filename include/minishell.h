
#ifndef MINISHELL_H
# define MINISHELL_H
# define PROMPT "minishell-> "
# include "../libft/libft.h"
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>

//-------ENUM STRUCTS-------//

typedef enum s_id_token
{
	DOLLAR,
	SPACE,
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


//--------TIM--------//
typedef struct	s_simple_cmd {
	char			*cmd_name;
	uint32_t		argc;		
	char			**argv;
	struct t_cmd	*next;
} 				t_simple_cmd;

typedef	int		(*t_builtin)();
//exec
int init_exec(t_simple_cmd *cmd);

//builtins
int f_echo(t_simple_cmd *cmd);
int	f_pwd(t_simple_cmd *cmd);

//utils
int ft_strcmp(const char *s1, const char *s2);
/*
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
	int				redir_count;
	int				fd_in;
	int				fd_out;
	char			**redir_files;
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
*/

#endif
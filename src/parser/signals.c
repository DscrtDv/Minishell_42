
#include"../../include/minishell.h"

static void init_terminal_attributes(void)
{
	struct termios terminal_attributes;

	tcgetattr(STDIN_FILENO, &terminal_attributes);
	terminal_attributes.c_lflag = terminal_attributes.c_lflag & ~ECHOCTL;
	//terminal_attributes.c_lflag = terminal_attributes.c_lflag | ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal_attributes);
}

static void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		exit_code = 130; // does not update!!
	}
}

void	init_signals(t_signal_modes mode)
{
	if (mode == NORMAL)
	{
		init_terminal_attributes();
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);		
	}
}

/*
Signals will behave differently depending on where in
the simulation they get called:

NORMAL --> reverts to normal behavior
CHILD --> child process
PARENT --> parent process
HEREDOC --> heredoc mode
*/

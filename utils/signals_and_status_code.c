#include "../include/minishell.h"

t_shell g_shell;

void	signal_handler(int sig)
{
	if (sig == SIGINT && g_shell.signel_cat == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		g_shell.signel_cat = 0;
}


void	handle_specific_signal(int signal_number)
{
	if (signal_number == SIGINT)
		printf("\n");
}


void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
		g_shell.exit_status = WEXITSTATUS(status);
}

void	display_status_code(int status)
{
	handle_exit_status(status);
	handle_specific_signal(status);
}

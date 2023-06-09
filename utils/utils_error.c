#include "../include/minishell.h"
t_shell g_shell;

void	print_error_cmd(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_shell.exit_status = 127;
}

void	print_error_file(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	print_error_fork(void)
{
	perror("fork");
	g_shell.exit_status = 1;
	exit(g_shell.exit_status);
}

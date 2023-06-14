/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 01:29:54 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/14 22:11:04 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	if_herdoc1(t_cmd *commands)
{
	commands->fd_in = open(commands->file_name, O_RDONLY);
	if (commands->fd_in == -1)
	{
		perror("open");
		g_shell.exit_status = 1;
		exit(g_shell.exit_status);
	}
	if (dup2(commands->fd_in, STDIN_FILENO) == -1)
	{
		perror("dup");
		g_shell.exit_status = 1;
		exit(g_shell.exit_status);
	}
	if (commands->fd_out != 1)
	{
		if (commands->fd_out == 101)
		{
			printf ("bash: outfile: Permission denie\n");
			g_shell.exit_status = 1;
			exit(g_shell.exit_status);
		}
		dup2(commands->fd_out, 1);
		close(commands->fd_out);
	}
	close(commands->fd_in);
	// unlink(commands->file_name);
}

void	if_input_output_file(t_cmd *commands)
{
	if (commands->fd_in != 0)
	{
		if (commands->fd_in == -1)
		{
			print_error_file(commands->file_name);
			g_shell.exit_status = 1;
			exit(g_shell.exit_status);
		}
		else
		{
			dup2(commands->fd_in, 0);
			close(commands->fd_in);
		}
	}
	if (commands->fd_out != 1)
	{
		if (commands->fd_out == 101)
		{
			printf ("bash: outfile: Permission denie\n");
			g_shell.exit_status = 1;
			exit(g_shell.exit_status);
		}
		dup2(commands->fd_out, 1);
		close(commands->fd_out);
	}
}
void ft_putnbr_fd(int n, int fd)
{
	char c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}
void	execute_child_process(t_cmd *commands, t_info *info, t_var *var)
{
	(void)var;
	char		*path;
	long long	nb;

	signal(SIGINT, signal_handler);
	if (commands->heredoc)
		if_herdoc1(commands);
	else
		if_input_output_file(commands);
	if (!ft_strcmp(commands->main_cmd, "minishell")
		|| !ft_strcmp(commands->main_cmd, "./minishell"))
	{
		path = ft_strdup("minishell");
		nb = ft_atoi(get_value2(info, "SHLVL"));
		set_value1(info, "SHLVL", ft_itoa(++nb));
	}
	else
		path = check_if_command_found(commands->main_cmd, &info->head_ex);
	if (execve(path, commands->cmds, create_env(info)) == -1)
	{
		print_error_cmd(commands->main_cmd);
		g_shell.exit_status = 127;
		exit(g_shell.exit_status);
	}
	else
	{
		perror("ls");
		g_shell.exit_status = 1;
		exit(g_shell.exit_status);
	}
}

int	execute_commande(t_cmd *commands, t_info *info,
	t_list *shell, t_var *var)
{

	signal(SIGINT, signal_handler);

	pid_t	pid;

	// g_shell.signel_cat = 1;
	if (is_builin(commands) == 1)
		return (builtin_execution(shell, info, 1, var), 0);
	else if (commands->main_cmd)
	{
		pid = fork();
		if (pid == -1)
			print_error_fork();
		signal(SIGINT, SIG_IGN);
		// g_shell.sig_ignore = 1;
		if (pid == 0)
		{
			if (commands->fd_in != 404 && commands->fd_out != 404)
			execute_child_process(commands, info, var);
		}
		if (pid != 0)
		{
			waitpid(pid, &g_shell.exit_status, 0);
			display_status_code(g_shell.exit_status);
			signal(SIGINT, signal_handler);
			// g_shell.sig_ignore = 0;
		}
	}
	else
		return (print_error_cmd(commands->main_cmd), g_shell.exit_status = 127);
	return (0);
}

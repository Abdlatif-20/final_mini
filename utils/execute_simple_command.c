/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:15:58 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/10 18:06:30 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	g_shell;

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
	close(commands->fd_in);
}

void	if_input_output_file(t_cmd *commands)
{
	if (commands->fd_in != 0)
	{
		if (commands->fd_in == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(commands->file_name, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
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
	{puts("here");
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

void	execute_child_process(t_cmd *commands, t_info *info)
{
	char	*path;

	if (commands->heredoc)
		if_herdoc1(commands);
	else
		if_input_output_file(commands);
	if (!ft_strcmp(commands->main_cmd, "minishell"))
		path = ft_strdup("minishell");
	else
		path = check_if_command_found(commands->main_cmd, &info->head_ex);
	if (execve(path, commands->cmds, create_env(info)) == -1)
	{
		print_error_cmd(commands->main_cmd);
		g_shell.exit_status = 127;
		exit(g_shell.exit_status);
	}
}

void	execute_commande(t_cmd *commands, t_info *info, t_list *shell)
{
	pid_t	pid;

	g_shell.signel_cat = 1;
	if (is_builin(commands) == 1)
	{
		builtin_execution(shell, info, 1);
		return ;
	}
	else if (commands->main_cmd)
	{
		pid = fork();
		if (pid == -1)
			print_error_fork();
		else if (pid == 0)
		{
			if (commands->fd_in != 404 && commands->fd_out != 404)
				execute_child_process(commands, info);
		}
		else
		{
			waitpid(pid, &g_shell.exit_status, 0);
			display_status_code(g_shell.exit_status);
		}
	}
}

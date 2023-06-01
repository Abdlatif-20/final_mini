/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:46:09 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/01 15:00:46 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void if_herdoc1(t_cmd *commands)
{
	commands->fd_in = open(commands->file_name, O_RDONLY);
	if (commands->fd_in == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(commands->fd_in, STDIN_FILENO) == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
	close(commands->fd_in);
}

void if_input_output_file(t_cmd *commands)
{
	if (commands->fd_in != 0) 
	{
		if (commands->fd_in == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(commands->file_name, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(EXIT_FAILURE);
		}
		else
		{
			dup2(commands->fd_in, 0);
			close(commands->fd_in);
		}
	}
	if (commands->fd_out != 1)
	{
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
	path = check_if_command_found(commands->main_cmd, &info->head_ex);
	if (!path)
		return ;
	if (execve(path, commands->cmds, NULL) == -1)
	{
		print_error_cmd(commands->main_cmd);
		exit(EXIT_FAILURE);
	}
}

void execute_commande(t_cmd *commands, t_info *info, t_list *shell)
{
	pid_t pid;
	int status;

	if (is_builin(commands) == 1)
	{
		builtin_execution(shell, info, 1);
		return ;
	}
	if (commands->main_cmd)
	{
		if (check_if_command_found(commands->main_cmd, &info->head_ex))
		{
			pid = fork();
			if (pid == -1) 
			{
				perror("fork");
				exit(EXIT_FAILURE);
			} 
			else if (pid == 0)
				execute_child_process(commands, info);
			else
				waitpid(pid, &status, 0);
		}
		else
			print_error_cmd(commands->main_cmd);
	}
}



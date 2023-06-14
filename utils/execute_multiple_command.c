/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 01:29:24 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/14 22:20:24 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	if_input_file(t_cmd *commands)
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
}

void	if_herdoc_or_inputfile(t_cmd *commands)
{
	if (commands->heredoc)
		if_herdoc(commands);
	else
		if_input_file(commands);
}

void	dup_for_pipes(int **pipefd, int i, int nb_pipes)
{
	if (i == 0)
		dup2(pipefd[i][1], STDOUT_FILENO);
	else if (i == nb_pipes)
		dup2(pipefd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		dup2(pipefd[i][1], STDOUT_FILENO);
	}
}

void	merge_dup_pipe_herdoc(int **pipefd, int i,
	int nb_pipes, t_cmd *commands)
{
	dup_for_pipes(pipefd, i, nb_pipes);
	close_pipe(pipefd, nb_pipes);
	if_herdoc_or_inputfile(commands);
	if (commands->fd_out != 1)
	{
		dup2(commands->fd_out, STDOUT_FILENO);
		close(commands->fd_out);
	}
}


void	execute_commands_with_pipe(t_list *cmd, t_info *info, int nb_pipes, t_var *var)
{
	int	**pipefd;

	var->nb_pipes = nb_pipes;
	pipefd = create_pipefd(var->nb_pipes);
	info->i = 0;
	while (info->i < var->nb_pipes)
	{
		create_pipe(pipefd[info->i]);
		info->i++;
	}
	info->commands = cmd->data;
	info->i = 0;
	while (info->i < var->nb_pipes + 1)
	{
		info->pid = fork();
		if (info->pid == -1)
			if(print_error_fork() == -1)
				return ;
		if (info->pid == 0)
			execute3(info, cmd, pipefd, var);
		info->i++;
		cmd = cmd->next;
		if (cmd)
			info->commands = cmd->data;
		// unlink(info->commands->file_name);
	}
	close_pipe(pipefd, var->nb_pipes);
	wait_for_child(var->nb_pipes);
	free_pipefd(pipefd, var->nb_pipes);
}

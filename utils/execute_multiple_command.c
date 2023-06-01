/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:15:49 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/01 21:39:02 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("Error: pipe failed\n", 2);
		exit(1);
	}
}

void close_pipe(int **pipefd, int nb_pipes)
{
	int i;

	i = 0;
	while (i < nb_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

void if_herdoc(t_cmd *commands)
{
	commands->fd_in = open(commands->file_name, O_RDONLY);
	if (commands->fd_in == 0)
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

void if_input_file(t_cmd *commands)
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
}

void if_herdoc_or_inputfile(t_cmd *commands)
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

void merge_dup_pipe_herdoc(int **pipefd, int i, int nb_pipes, t_cmd *commands)
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

void wait_for_child(int nb_pipes)
{
	int i;

	i = 0;
	while (i < nb_pipes + 1)
	{
		wait(NULL);
		i++;
	}
}

int **create_pipefd(int nb_pipes)
{
	int **pipefd;
	int i;

	i = 0;
	pipefd = (int **)malloc(sizeof(int *) * nb_pipes);
	while (i < nb_pipes)
	{
		pipefd[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	return (pipefd);
}


void execute_commands_with_pipe(t_list *cmd, t_info *info, int nb_pipes)
{
	int **pipefd;
	
	pipefd = create_pipefd(nb_pipes);
	info->i = 0;
	while (info->i < nb_pipes)
	{
		create_pipe(pipefd[info->i]);
		info->i++;
	}
	info->commands = cmd->data;
	info->i = 0;
	while (info->i < nb_pipes + 1)
	{
		info->pid = fork();
		if (info->pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (info->pid == 0)
		{
			merge_dup_pipe_herdoc(pipefd, info->i, nb_pipes, info->commands);
			info->temp = check_if_command_found (info->commands->main_cmd,
					&info->head_ex);
			if (is_builin(info->commands) == 1)
			{
				builtin_execution(cmd, info, 0);
				exit(EXIT_SUCCESS);
			}
			if (info->commands->main_cmd)
			{
				if (execve(info->temp, info->commands->cmds, create_env(info)) == -1)
				{
					print_error_cmd(info->commands->main_cmd);
					exit(EXIT_FAILURE);
				}
			}
			exit(EXIT_SUCCESS);
		}
		info->i++;
		cmd = cmd->next;
		if (cmd)
			info->commands = cmd->data;
	}
	close_pipe(pipefd, nb_pipes);
	wait_for_child(nb_pipes);
}

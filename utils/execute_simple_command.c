/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:46:09 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/03 20:43:00 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
t_shell g_shell;


char **create_env(t_info *info)
{
	t_env	*tmp;
	char	**env;
	int		i;

	i = 0;
	tmp = info->head_en;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = info->head_en;
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->env_var, "=");
		env[i] = ft_strjoin(env[i], tmp->env_value);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

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
	if (execve(path, commands->cmds, create_env(info)) == -1)
	{
		print_error_cmd(commands->main_cmd);
		exit(EXIT_FAILURE);
	}
}

// char **create_env(t_info *info)
// {
// 	t_env	*tmp;
// 	char	**env;
// 	int		i;

// 	i = 0;
// 	tmp = info->head_en;
// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	env = (char **)malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	tmp = info->head_en;
// 	while (tmp)
// 	{
// 		env[i] = ft_strjoin(tmp->env_var, "=");
// 		env[i] = ft_strjoin(env[i], tmp->env_value);
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	env[i] = NULL;
// 	return (env);
// }



void execute_commande(t_cmd *commands, t_info *info, t_list *shell)
{
	pid_t pid;
	// int status;

	// status = 0;
	if (is_builin(commands) == 1)
	{
		builtin_execution(shell, info, 1);
		return ;
	}
	else if (commands->main_cmd)
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
			{
				waitpid(pid, &g_shell.exit_status, 0);
				display_status_code(g_shell.exit_status);
			}
		}
		else
		{
			print_error_cmd(commands->main_cmd);
			// display_status_code(g_shell.exit_status);
		}
	}
	printf("the exit status is %d\n", g_shell.exit_status);
}



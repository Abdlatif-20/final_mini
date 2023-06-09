/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:43:47 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/09 23:04:44 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_env(t_info *info)
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
	if (!env)
		return (NULL);
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

void	if_herdoc(t_cmd *commands)
{
	commands->fd_in = open(commands->file_name, O_RDONLY);
	if (commands->fd_in == 0)
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

void	execute1(t_list *cmd, t_info *info)
{
	builtin_execution(cmd, info, 0);
	g_shell.exit_status = 0;
	exit(g_shell.exit_status);
}

void	execute2(t_info *info)
{
	if (execve(info->temp, info->commands->cmds, create_env(info)) == -1)
	{
		print_error_cmd(info->commands->main_cmd);
		g_shell.exit_status = 127;
		exit(g_shell.exit_status);
	}
}

void	execute3(t_info *info, t_list *cmd, int **pipefd, int nb_pipes)
{
	merge_dup_pipe_herdoc(pipefd, info->i, nb_pipes, info->commands);
	info->temp = check_if_command_found (info->commands->main_cmd,
			&info->head_ex);
	if (is_builin(info->commands) == 1)
		execute1(cmd, info);
	else if (info->commands->main_cmd)
		execute2(info);
	exit(g_shell.exit_status);
}

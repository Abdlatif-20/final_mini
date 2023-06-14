/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:43:47 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/14 17:24:22 by aben-nei         ###   ########.fr       */
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(commands->file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_shell.exit_status = 1;
		exit(g_shell.exit_status);
	}
	close(commands->fd_in);
	unlink(commands->file_name);
}

void	execute1(t_list *cmd, t_info *info, t_var *var)
{
	builtin_execution(cmd, info, 0, var);
	g_shell.exit_status = 0;
	exit(g_shell.exit_status);
}

void	execute2(t_info *info, t_var *var)
{
	// (void)var;
	if (!var->is_empty_str && execve(info->temp, info->commands->cmds, create_env(info)) == -1)
	{
		print_error_cmd(info->commands->main_cmd);
		g_shell.exit_status = 127;
		exit(g_shell.exit_status);
	}
	else
	{
		printf("minishell: : command not found\n");
		g_shell.exit_status = 127;
		exit(g_shell.exit_status);
	}
}

void	execute3(t_info *info, t_list *cmd, int **pipefd, t_var *var)
{
	merge_dup_pipe_herdoc(pipefd, info->i, var->nb_pipes, info->commands);
	info->temp = check_if_command_found (info->commands->main_cmd,
			&info->head_ex);
	if (is_builin(info->commands) == 1)
		execute1(cmd, info, var);
	else if (info->commands->main_cmd)
		execute2(info, var);
	exit(g_shell.exit_status);
}

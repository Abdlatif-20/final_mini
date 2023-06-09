/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:41:51 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/09 23:13:06 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dup_for_builin(t_cmd *commands)
{
	if (commands->fd_in != 0)
	{
		dup2(commands->fd_in, STDIN_FILENO);
		close(commands->fd_in);
	}
	if (commands->fd_out != 1)
	{
		dup2(commands->fd_out, STDOUT_FILENO);
		close(commands->fd_out);
	}
}

void	builint_simple(t_cmd *commands, t_info *info)
{
	if (!ft_strcmp(commands->main_cmd, "echo"))
		my_echo(commands);
	else if (!ft_strcmp(commands->main_cmd, "cd"))
		my_cd(commands, info);
	else if (!ft_strcmp(commands->main_cmd, "pwd"))
		my_pwd(info);
	else if (!ft_strcmp(commands->main_cmd, "exit"))
		my_exit(commands);
	else if (info->head_en && info->head_ex
		&& !ft_strcmp(commands->main_cmd, "unset"))
		my_unset(commands, info);
}

void	builint_complex(t_cmd *commands, t_info *info)
{
	if ((!ft_strcmp(commands->main_cmd, "export")) && !commands->cmds[1])
		print_list_export(info);
	if (info->head_en && !ft_strcmp(commands->main_cmd, "env")
		&& !commands->cmds[1])
		print_list_env(info);
	else if ((!ft_strcmp(commands->main_cmd, "export") && commands->cmds[1]))
	{
		if (info->head_en && check_export(commands->cmds) == 0)
			return ;
		if (info->head_en && commands->cmds)
		{
			add_export(&info->head_ex, commands->cmds);
			add_env(&info->head_en, commands->cmds);
			g_shell.exit_status = 0;
		}
	}
}

void	builtin_execution(t_list *shell, t_info *info, int flag)
{
	t_cmd	*commands;

	commands = shell->data;
	if (flag == 1)
		dup_for_builin(commands);
	if (!commands || !commands->cmds[0])
		return ;
	else if (is_builin(commands))
	{
		builint_simple(commands, info);
		builint_complex(commands, info);
	}
}

void	choose_command(t_list *shell, t_info *info)
{
	t_cmd	*commands;
	int		nb_cmd;
	int		nb_node;

	// if (g_shell.signel_hedoc)
	// 	return ;
	info->in = dup(STDIN_FILENO);
	info->out = dup(STDOUT_FILENO);
	if (!shell || !shell->data || !info)
		return ;
	commands = shell->data;
	nb_cmd = ft_lstsize(shell);
	nb_node = get_nbr_node(shell);
	if (nb_node == 1)
		execute_commande(commands, info, shell);
	else if (nb_node > 1 && g_shell.signel_hedoc == 0)//check
		execute_commands_with_pipe(shell, info, --nb_cmd);
	dup2(info->in, STDIN_FILENO);
	dup2(info->out, STDOUT_FILENO);
	close(info->in);
	close(info->out);
}

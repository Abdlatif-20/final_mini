/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:51:36 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/16 01:58:35 by ahaloui          ###   ########.fr       */
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

int	builint_simple(t_cmd *commands, t_info *info, t_var *var)
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
		&& !ft_strcmp(commands->main_cmd, "unset") && commands->cmds[1])
	{
		if (var->is_empty_str)
			return (505);
		else
			my_unset(commands, info);
	}
	return (0);
}

void	builint_complex(t_cmd *commands, t_info *info, t_var *var)
{
	int	nb;

	nb = count_str(commands->cmds);
	if ((info->head_ex && !ft_strcmp(commands->main_cmd, "export") && nb == 1)
		|| (var->is_empty_str && nb == 2))
		print_list_export(info);
	else if (!ft_strcmp(commands->main_cmd, "export") && nb > 1)
	{
		if (info->head_en && check_export(commands->cmds, var) == 0)
			return ;
		if (info->head_en && commands->cmds)
		{
			add_export(&info->head_ex, commands->cmds);
			add_env(&info->head_en, commands->cmds);
			g_shell.exit_status = 0;
		}
	}
	else if (info->head_en && !ft_strcmp(commands->main_cmd, "env") && nb == 1)
		print_list_env(info);
}

void	builtin_execution(t_list *shell, t_info *info, int flag, t_var *var)
{
	t_cmd	*commands;

	commands = shell->data;
	if (flag == 1)
		dup_for_builin(commands);
	if (!commands || !commands->cmds[0])
		return ;
	else if (is_builin(commands))
	{
		if (builint_simple(commands, info, var) == 505)
			return ;
		else
			builint_complex(commands, info, var);
	}
}

void	choose_command(t_list *shell, t_info *info, t_var *var)
{
	t_cmd	*commands;
	int		nb_cmd;
	int		nb_node;

	if (g_shell.signel_hedoc)
		return ;
	info->in = dup(STDIN_FILENO);
	info->out = dup(STDOUT_FILENO);
	if (!shell || !shell->data || !info)
		return ;
	commands = shell->data;
	nb_cmd = ft_lstsize(shell);
	nb_node = get_nbr_node(shell);
	if (nb_node == 1)
	{
		execute_commande(commands, info, shell, var);
		close(commands->fd_in);
		close(commands->fd_out);
	}
	else if (nb_node > 1)
		execute_commands_with_pipe(shell, info, --nb_cmd, var);
	dup2(info->in, STDIN_FILENO);
	dup2(info->out, STDOUT_FILENO);
	close(info->in);
	close(info->out);
}

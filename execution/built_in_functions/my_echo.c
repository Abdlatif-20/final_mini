/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:40:39 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/13 23:59:02 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_last_split(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->cmds[i])
		return (NULL);
	while (cmd->cmds[i])
		i++;
	return (cmd->cmds[i - 1]);
}

int	check_option(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	if (cmd[i] == '-')
		i++;
	else
		return (0);
	if (cmd[i] == '\0')
		return (0);
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	help_echo(int i, t_cmd *cmd)
{
	if (!cmd->cmds[i])
		return (0);
	ft_putstr_fd(cmd->cmds[i], 1);
	if (cmd->cmds[i + 1])
		ft_putstr_fd(" ", 1);
	g_shell.exit_status = 0;
	return (1);
}

int	my_echo(t_cmd *cmd)
{
	int	i;
	int	find_option;
	int	not_option;

	i = 1;
	find_option = 0;
	not_option = 0;
	if (!check_option(cmd->cmds[i]))
		not_option = 1;
	while (cmd->cmds[i])
	{
		if (find_option == 0 && !not_option)
		{
			while (check_option(cmd->cmds[i]))
			{
				i++;
				find_option = 1;
			}
		}
		help_echo(i, cmd);
		i++;
	}
	if (find_option == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:48:01 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/08 16:38:50 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



int check_is_numeric(char *split)
{
	int i;

	i = 0;
	while (split[i])
	{
		if ((split[i] == '-' && i == 0) || (split[i] == '+' && i == 0 && ft_isdigit(split[i + 1])))
			i++;
		if (!ft_isdigit(split[i]))
			return (0);
		i++;
	}
	return (1);
}

int check_white_spaces(char *split)
{
	int i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
	{
		if (!ft_whitespace(split[i]))
			return (0);
		i++;
	}
	return (1);
}

// void 

int my_exit(t_cmd *commands)
{
	int i;
	int flag;
	long long status_code;
	i = 1;
	status_code = 0;
	flag = 0;
	if (check_white_spaces(commands->cmds[i]))
	{
		printf("exit\n");
		printf("minishell: exit: %s :numeric argument required\n", commands->cmds[i]);
		g_shell.exit_status = 255;
		exit(g_shell.exit_status);
	}
	commands->cmds[i] = skip_whitespace(commands->cmds[i]);
	if (commands->cmds[i])
	{
		if (check_is_numeric(commands->cmds[i]) && !commands->cmds[i + 1])
		{
			status_code = ft_atoi1(commands->cmds[i], &flag);
			if (status_code >= 0 && !flag)
			{
				if ((status_code >= 0 && status_code <= 255))
					g_shell.exit_status = status_code;
				else if (status_code > 255)
					g_shell.exit_status = status_code % 256;
				printf("exit\n");
				g_shell.exit_status = status_code;
				exit(g_shell.exit_status);
			}
			else if (status_code < 0 && !flag)
			{
				printf("exit\n");
				g_shell.exit_status = status_code + 256;
				exit(g_shell.exit_status);
			}
			else
			{
				printf("exit\n");
				printf("minishell: exit: %s: numeric argument required\n", commands->cmds[i]);
				g_shell.exit_status = 255;
				exit (g_shell.exit_status);
			}
		}
		else if (check_is_numeric(commands->cmds[i]) && check_is_numeric(commands->cmds[i + 1]))
		{
			printf("exit\n");
			printf("minishell: exit: too many arguments\n");
			g_shell.exit_status = 1;
			return (g_shell.exit_status);
		}
		else if ((!check_is_numeric(commands->cmds[i]) || (status_code == -1 && flag)))
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", commands->cmds[i]);
			g_shell.exit_status = 255;
			exit (g_shell.exit_status);
		}
	}
	else
	{
		printf("exit\n");
		g_shell.exit_status = 127;
		exit(g_shell.exit_status);
	}
	return (0);
}

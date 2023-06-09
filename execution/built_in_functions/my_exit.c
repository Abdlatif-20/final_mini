/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:48:01 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/09 23:37:50 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_is_numeric(char *split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
	{
		if ((split[i] == '-' && i == 0) || (split[i] == '+' && i == 0
				&& ft_isdigit(split[i + 1])))
			i++;
		if (!ft_isdigit(split[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_white_spaces(char *split)
{
	int	i;

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

void	case1(t_cmd *commands, int i)
{
	ft_putstr_fd("exit\n", 2);
	printf("minishell: exit: %s :numeric argument required\n", commands->cmds[i]);
	g_shell.exit_status = 255;
	exit(g_shell.exit_status);
}

int case2()
{
	printf("exit\n");
	printf("minishell: exit: too many arguments\n");
	g_shell.exit_status = 1;
	return (g_shell.exit_status);
}

void case_positive(long long status_code)
{
	if ((status_code >= 0 && status_code <= 255))
		g_shell.exit_status = status_code;
	else if (status_code > 255)
		g_shell.exit_status = status_code % 256;
	printf("exit\n");
	g_shell.exit_status = status_code;
	exit(g_shell.exit_status);
}

void case_negative(long long status_code)
{
	printf("exit\n");
	g_shell.exit_status = status_code + 256;
	exit(g_shell.exit_status);
}

void default_case()
{
	printf("exit\n");
	g_shell.exit_status = 127;
	exit(g_shell.exit_status);
}

void special_case(t_cmd *commands, int i, int flag)
{
	printf("exit--------\n");
	(void)flag;
	printf("exit\n");
	printf("minishell: exit: %s: numeric argument required\n", commands->cmds[i]);
	if (!check_is_numeric(commands->cmds[i]) && (!check_is_numeric(commands->cmds[i + 1])))
		g_shell.exit_status = 255;
	else
		g_shell.exit_status = 1;
	exit(g_shell.exit_status);
}

void help_case(t_cmd *commands, int i, int flag, long long *status_code)
{
	if (check_is_numeric(commands->cmds[i]) && !commands->cmds[i + 1])
	{
		*status_code = ft_atoi1(commands->cmds[i], &flag);
		if (*status_code >= 0 && !flag)
			case_positive(*status_code);
		else if (*status_code < 0 && !flag)
			case_negative(*status_code);
		else
			case1(commands, i);
	}
	else if (check_is_numeric(commands->cmds[i]) && check_is_numeric(commands->cmds[i + 1]))
		case2();
	else if (check_is_numeric(commands->cmds[i]) && !check_is_numeric(commands->cmds[i + 1]))
		case2();
	else if ((!check_is_numeric(commands->cmds[i]) || (*status_code == -1 && flag)))
		special_case(commands, i, flag);
}

int my_exit(t_cmd *commands)
{
	int i;
	int flag;
	long long status_code;

	i = 1;
	status_code = 0;
	flag = 0;
	if (check_white_spaces(commands->cmds[i]))
		case1(commands, i);
	commands->cmds[i] = skip_whitespace(commands->cmds[i]);
	if (commands->cmds[i])
		help_case(commands, i, flag, &status_code);
	else
		default_case();
	return (0);
}

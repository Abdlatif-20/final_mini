/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:41:21 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/15 01:58:00 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	case1(t_cmd *commands, int i)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("miishell: exit: ", 2);
	ft_putstr_fd(commands->cmds[i], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_shell.exit_status = 255;
	exit(g_shell.exit_status);
}

int	case2(void)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd("too many arguments\n", 2);
	g_shell.exit_status = 1;
	return (g_shell.exit_status);
}

void	case_positive(long long status_code)
{
	if ((status_code >= 0 && status_code <= 255))
		g_shell.exit_status = status_code;
	else if (status_code > 255)
		g_shell.exit_status = status_code % 256;
	printf("exit\n");
	g_shell.exit_status = status_code;
	exit(g_shell.exit_status);
}

void	case_negative(long long status_code)
{
	printf("exit\n");
	g_shell.exit_status = status_code + 256;
	exit(g_shell.exit_status);
}

void	default_case(void)
{
	printf("exit\n");
	g_shell.exit_status = 127;
	exit(g_shell.exit_status);
}

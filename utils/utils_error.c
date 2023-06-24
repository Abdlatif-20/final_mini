/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.ma>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:37:27 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/24 02:39:32 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error_cmd(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_shell.exit_status = 127;
}

void	print_error_file(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_shell.exit_status = 127;
}

int	print_error_fork(void)
{
	ft_putstr_fd("fork ", 2);
	g_shell.exit_status = 1;
	return (g_shell.exit_status);
}

void	print_error_variable(char *variable)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(variable, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	help_create_pipefd(t_var *var, int **pipefd, t_info *info)
{
	info->i = 0;
	while (info->i < var->nb_pipes)
	{
		create_pipe(pipefd[info->i]);
		info->i++;
	}
}

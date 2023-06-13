/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:37:27 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/14 00:37:39 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_shell g_shell;

void	print_error_cmd(char *command)
{
	if (!command)
		return ;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_shell.exit_status = 127;
}

void	print_error_file(char *command)
{
	if (!command)
		return ;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	print_error_fork(void)
{
	perror("fork");
	g_shell.exit_status = 1;
	exit(g_shell.exit_status);
}

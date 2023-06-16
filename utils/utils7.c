/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:01:01 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/16 03:02:28 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	**create_pipefd(int nb_pipes)
{
	int	**pipefd;
	int	i;

	i = 0;
	pipefd = (int **)malloc(sizeof(int *) * nb_pipes);
	if (!pipefd)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		g_shell.exit_status = 1;
		exit(g_shell.exit_status);
	}
	while (i < nb_pipes)
	{
		pipefd[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	return (pipefd);
}

void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("Error: pipe failed\n", 2);
		g_shell.exit_status = 1;
		exit(g_shell.exit_status);
	}
}

void	close_pipe(int **pipefd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

void	wait_for_child(int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes + 1)
	{
		waitpid(-1, &g_shell.exit_status, 0);
		display_status_code(g_shell.exit_status);
		i++;
	}
}

int	get_nbr_node(t_list *shell)
{
	int	i;

	i = 0;
	while (shell)
	{
		i++;
		shell = shell->next;
	}
	return (i);
}

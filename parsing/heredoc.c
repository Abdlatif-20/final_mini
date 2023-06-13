/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:00:30 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/13 05:22:59 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*generate_name(void)
{
	static int	i;
	char		*name;
	char		*num;

	name = ft_strdup("/tmp/heredoc");
	num = ft_itoa(i);
	name = ft_strjoin(name, num);
	name = ft_strjoin(name, ".txt");
	i++;
	return (free(num), name);
}

int	get_0(void)
{
	return (0);
}

void	handel(int SIG)
{
	(void)SIG;
	rl_done = 1;
	g_shell.signel_hedoc = 1;
}

void	ft_heredoc(t_list *args, int *fd, char **file, t_env *env)
{
	char	*name;

	name = NULL;
	while (args)
	{
		if (g_shell.signel_hedoc)
			break ;
		if (((t_token *)args->data)->key == HEREDOC)
		{
			name = generate_name();
			(*fd) = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
			ft_free(*file);
			*file = ft_strdup(name);
			((t_token *)args->data)->key = RED_INP;
			free(((t_token *)args->data)->value);
			((t_token *)args->data)->value = ft_strdup("<");
			args = args->next;
			if (!args)
			{
				free(name);
				break ;
			}
			if (((t_token *)args->data)->key == W_SPACE)
					args = args->next;
			heredoc_helper(&args, name, fd, env);
			free(name);
		}
		args = args->next;
	}
}

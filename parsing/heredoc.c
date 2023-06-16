/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:00:30 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/17 00:05:13 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*generate_name(void)
{
	int		fd;
	short	s;
	char	*name;
	char	*num;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &s, sizeof(short));
	name = ft_strdup("/tmp/here_");
	num = ft_itoa(s);
	name = ft_strjoin(name, num);
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

	if (((t_token *)args->data)->key == HEREDOC)
	{
		name = generate_name();
		if ((*fd) == -1)
		{
			return (free(name));
		}
		(*fd) = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);
		ft_free(*file);
		*file = ft_strdup(name);
		((t_token *)args->data)->key = RED_INP;
		free(((t_token *)args->data)->value);
		((t_token *)args->data)->value = ft_strdup("<");
		args = args->next;
		if (!args)
			return ;
		if (((t_token *)args->data)->key == W_SPACE)
				args = args->next;
		heredoc_helper(&args, name, fd, env);
		free(name);
	}
}

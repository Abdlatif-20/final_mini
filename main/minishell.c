/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:38:05 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/17 16:38:08 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_list	*args;
	t_list	*cmd;
	t_info	info;
	t_var	var;

	init_main(&args, &cmd, &info, &var);
	if (argc != 1)
		return (printf(ERR_ARG, argv[1]), 0);
	if (env == NULL || *env == NULL)
	{
		add_export_ignored(&info);
		add_env_ignored(&info);
	}
	fill_export_list(env, &info.head_ex);
	fill_env_list(env, &info.head_en);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	printf("\033[2J\033[1;1H");
	ft_loop(&args, &cmd, &info, &var);
	free_export(&info.head_ex);
	free_env(&info.head_en);
	return (0);
}

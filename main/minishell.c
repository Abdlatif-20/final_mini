/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:01:55 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/14 15:08:57 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// void	print_list1(t_list *cmd)
// {
// 	if (!cmd)
// 		return ;
// 	t_list *tmp = cmd;
// 	t_token *token = cmd->data;
// 	while (tmp)
// 	{
// 		token = tmp->data;
// 		printf("key = [%d] | value = [%s]\n", token->key, token->value);
// 		tmp = tmp->next;
// 	}
// }
// void	print_list11(t_list *cmd)
// {
// 	if (!cmd)
// 		return ;
// 	t_list *tmp = cmd;
// 	t_cmd *token = cmd->data;
// 	while (tmp)
// 	{
// 		int	i = 0;
// 		token = tmp->data;
// 		while (tmp && token->cmds[i] && token->cmds)
// 		{
// 			printf("cmd = [%s]\n",token->cmds[i]);
// 			i++;
// 		}
// 		printf ("main_cmd = [%s]\n", token->main_cmd);
// 		printf ("fd_in = [%d]\n", token->fd_in);
// 		printf ("fd_out = [%d]\n", token->fd_out);
// 		printf("file_name = [%s]\n", token->file_name);
// 		tmp = tmp->next;
// 	}
// }

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
	printf("\033[2J\033[1;1H");
	ft_loop(&args, &cmd, &info, &var);
	free_export(&info.head_ex);
	free_env(&info.head_en);
	return (0);
}

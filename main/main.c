/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:21:46 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/14 00:32:48 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	print_list1(t_list *cmd)
{
	if (!cmd)
		return ;
	t_list *tmp = cmd;
	t_token *token = cmd->data;
	while (tmp)
	{
		token = tmp->data;
		printf("key = [%d] | value = [%s]\n", token->key, token->value);
		tmp = tmp->next;
	}
}
void	print_list11(t_list *cmd)
{
	if (!cmd)
		return ;
	t_list *tmp = cmd;
	t_cmd *token = cmd->data;
	while (tmp)
	{
		int	i = 0;
		token = tmp->data;
		while (tmp && token->cmds[i] && token->cmds)
		{
			printf("cmd = [%s]\n",token->cmds[i]);
			i++;
		}
		printf ("main_cmd = [%s]\n", token->main_cmd);
		printf ("fd_in = [%d]\n", token->fd_in);
		printf ("fd_out = [%d]\n", token->fd_out);
		printf("file_name = [%s]\n", token->file_name);
		tmp = tmp->next;
	}
}



int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_list	*args;
	t_list	*cmd;
	t_info	info;
	t_var	var;

	(void)var;
	args = NULL;
	cmd = NULL;
	input = NULL;
	info.head_ex = NULL;
	info.head_en = NULL;
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
	while (42)
	{
		rl_catch_signals = 0;
		g_shell.signel_hedoc = 0;
		input = readline("-> minishell$ ");
		if (input)
		{
			add_history(input);
			if (check_quotes(input))
			{
				free(input);
				printf("minishell: quotes not closed\n");
				continue ;
			}
			get_token(input, &args);
			if (args && syntex_error(args))
			{
				free_token_list(&args);
				free(input);
				continue ;
			}
			ft_trim_quotes(&args);
			ft_expand(&args, info.head_en);
			ft_join_args(&args);
			command_table(args, &cmd, info.head_en, &var);
			if (cmd && cmd->data)
				choose_command(cmd, &info, &var);
			free_token_list(&args);
			free_list_cmd(&cmd);
			free (input);
		}
		else
		{
			printf(" exit\n");
			free_token_list(&args);
			free_list_cmd(&cmd);
			free(input);
			break ;
		}
	}
	free_export(&info.head_ex);
	free_env(&info.head_en);
	return (0);
}

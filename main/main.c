/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:32:01 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/01 13:06:33 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// #include "../libft/libft.h"

// void	print_list1(t_list *cmd)
// {
// 	int i = 0;
// 	if (!cmd)
// 		return ;
// 	t_list *tmp = cmd;
// 	t_cmd *token = cmd->data;
// 	while (tmp)
// 	{
// 		token = tmp->data;
// 		i = 0;
// 		while (tmp && token->cmds[i])
// 		{
// 			printf("tmp[%d] = %s\n", i, token->cmds[i]);
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		printf("\nCtrl+D (EOF) received. Exiting...\n");
		exit(0);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_list	*args;
	t_list	*cmd;
	t_info	*info;

	(void)argc;
	(void)argv;
	info = NULL;
	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
		return (0);
	args = NULL;
	cmd = NULL;
	input = NULL;
	info->head_ex = NULL;
	info->head_en = NULL;
	fill_export_list(env, &info->head_ex);
	fill_env_list(env, &info->head_en);

	// *********************************************
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	// *********************************************

	printf("\033[2J\033[1;1H");
	while (42)
	{
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
				ft_lstclear(&args);
				continue ;
			}
			ft_trim_quotes(&args);
			ft_expand(&args, info->head_en);
			ft_join_args(&args);
			// token = args->next->next->data;
			// printf("token->cmd = %s\n", token->value);
			command_table(args, &cmd);
			if (cmd && cmd->data)
				choose_command(cmd, info);
			ft_lstclear(&args);
			ft_lstclear(&cmd);
			free (input);
		}
		else
		{
			free(input);
			printf(" exit\n");
			break ;
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.ma>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:15:37 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/25 02:35:31 by aben-nei         ###   ########.fr       */
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
// 		printf("-----------------------------------\n");
// 		while (tmp && token->cmds[i] && token->cmds)
// 		{
// 			printf("cmd = [%s]\n",token->cmds[i]);
// 			i++;
// 		}
// 		printf ("main_cmd = [%s]\n", token->main_cmd);
// 		printf ("fd_in = [%d]\n", token->fd_in);
// 		printf ("fd_out = [%d]\n", token->fd_out);
// 		printf("file_name = [%s]\n", token->file_name);
// 		printf("file_heredoc = [%s]\n", token->file_name_heredoc);
// 		tmp = tmp->next;
// 	}
// }

void	main_helper(t_list **args, t_list **cmd, t_info *info, t_var *var)
{
	ft_trim_quotes(args);
	// print_list1(*args);
	var->is_empty_str = ft_expand(args, (*info).head_en, var);
	ft_join_args(args);
	command_table(*args, cmd, (*info).head_en, var);
	info->var = var;
	if ((*cmd) && (*cmd)->data)
		choose_command((*cmd), info, var);
	// print_list11(*cmd); 
	unlink_heredoc(var->heredoc_names, var->len);
	free_heredocs(var->heredoc_names, var->len);
	free_token_list(args);
	free_list_cmd(cmd);
}

void	init_main(t_list **args, t_list **cmd, t_info *info, t_var *var)
{
	(*args) = NULL;
	(*cmd) = NULL;
	(*info).head_ex = NULL;
	(*info).head_en = NULL;
	var->input = NULL;
	var->is_empty_str = 0;
	var->flag_bultin = 0;
	var->flag_home = 0;
	var->flag_path = 0;
	var->flag_expand = 0;
	var->flag_herdoc = 0;
}

int	main_helper2(t_list **args, t_list **cmd, t_info *info, t_var *var)
{
	(void)info;
	(void)cmd;
	add_history(var->input);
	if (check_quotes(var->input))
	{
		free(var->input);
		ft_putstr_fd("minishell: quotes not closed\n", 2);
		return (2);
	}
	get_token(var->input, args, &var->flag_expand);
	if (*args && syntex_error(*args))
	{
		free_token_list(args);
		free(var->input);
		return (3);
	}
	main_helper(args, cmd, info, var);
	free (var->input);
	return (0);
}

void	break_while(t_list *args, t_list *cmd, t_var *var)
{
	ft_putstr_fd("exit\n", 2);
	free_token_list(&args);
	free_list_cmd(&cmd);
	free(var->input);
}

void	ft_loop(t_list **args, t_list **cmd, t_info *info, t_var *var)
{
	while (42)
	{
		rl_catch_signals = 0;
		g_shell.signel_hedoc = 0;
		var->input = readline("-> minishell$ ");
		if (var->input)
			main_helper2(args, cmd, info, var);
		else
		{
			break_while(*args, *cmd, var);
			break ;
		}
	}
}

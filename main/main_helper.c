/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:51:18 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/16 03:56:50 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unlink_heredoc(char **file_names, int size)
{
	int	i;

	if (!file_names)
		return ;
	i = 0;
	while (i < size)
	{
		unlink(file_names[i]);
		i++;
	}
}

void	main_helper(t_list **args, t_list **cmd, t_info *info, t_var *var)
{
	ft_trim_quotes(args);
	var->is_empty_str = ft_expand(args, (*info).head_en);
	ft_join_args(args);
	command_table(*args, cmd, (*info).head_en, var);
	// print_list11(*cmd);
	if ((*cmd) && (*cmd)->data)
		choose_command((*cmd), info, var);
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
}

int	main_helper2(t_list **args, t_list **cmd, t_info *info, t_var *var)
{
	add_history(var->input);
	if (check_quotes(var->input))
	{
		free(var->input);
		ft_putstr_fd("minishell: quotes not closed\n", 2);
		return (2);
	}
	get_token(var->input, args);
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

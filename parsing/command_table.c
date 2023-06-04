/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:31:15 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/04 16:07:16 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	increment_args(t_list ***args, t_token **token)
{
	(**args) = (**args)->next;
	if (**args)
		*token = (**args)->data;
}

void	handel_rederections(t_list **args, t_var *var, t_token **token, t_env *env)
{
	if (*token && (*token)->key == RED_OUT)
	{
		rederection_out(*args, &var->fd_out);
		increment_args(&args, token);
	}
	if (*token && (*token)->key == RED_INP)
	{
		rederection_in((*args), &var->fd_in, &var->file_name);
		increment_args(&args, token);
	}
	else if (*token && (*token)->key == RED_APP)
	{
		rederection_app((*args), &var->fd_out);
		increment_args(&args, token);
	}
	else if (*token && (*token)->key == HEREDOC)
	{
		var->heredoc = 1;
		ft_heredoc((*args), &var->fd_in, &var->file_name, env);
		increment_args(&args, token);
	}
}

void	skip_pipe(t_list **args, t_list **tmp, t_token *token)
{
	if (token && token->key == PIPE)
	{
		(*args) = (*args)->next;
		token = (*args)->data;
		(*tmp) = (*args);
	}
}

void	init_var(t_var *var)
{
	var->heredoc = 0;
	var->fd_in = 0;
	var->fd_out = 1;
}

void	command_table(t_list *args, t_list **cmd, t_env *env)
{
	t_token	*token;
	t_var	var;

	var.tmp = args;
	while (args)
	{
		init_var(&var);
		token = args->data;
		while (args && token->key != PIPE)
		{
			if (args && (token->key == RED_OUT || token->key == RED_INP
					|| token->key == RED_APP || token->key == HEREDOC))
				handel_rederections(&args, &var, &token, env);
			else
			{
				args = args->next;
				if (!args)
					break ;
				token = args->data;
			}
		}
		fill_cmd(cmd, var, get_command1(var.tmp), var.heredoc);
		if (args)
			skip_pipe(&args, &var.tmp, token);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.ma>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:31:15 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/24 03:48:01 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	increment_args(t_list **args, t_token **token)
{
	(*args) = (*args)->next;
	if (*args)
		*token = (*args)->data;
}

void	handel_redere(t_list **args, t_var *var, t_token **token, t_env *env)
{
	if (*token && (*token)->key == RED_OUT)
	{
		rederection_out(*args, &var->fd_out, var);
		increment_args(args, token);
	}
	if (*token && (*token)->key == RED_INP)
	{
		rederection_in((*args), &var->fd_in, &var->file_name);
		increment_args(args, token);
	}
	else if (*token && (*token)->key == RED_APP)
	{
		rederection_app((*args), &var->fd_out);
		increment_args(args, token);
	}
	else if (*token && (*token)->key == HEREDOC)
	{
		var->heredoc = 1;
		var->env = env;
		ft_heredoc((*args), &var->fd_in, &var->file_name, var);
		var->file_name_herdoc = var->file_name;
		increment_args(args, token);
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

void	command_table_help(t_var *var, t_list *args)
{
	var->tmp = args;
	var->heredoc_names = NULL;
	var->file_name_herdoc = NULL;
	var->len = herdoc_count(args);
	if (var->len > 0)
	{
		var->heredoc_names = malloc((herdoc_count(args) + 1) * sizeof(char *));
		if (!var->heredoc_names)
			return ;
		var->heredoc_names[herdoc_count(args)] = NULL;
	}
}

void	command_table(t_list *args, t_list **cmd, t_env *env, t_var	*var)
{
	t_token	*token;
	int		i;

	i = 0;
	command_table_help(var, args);
	while (args)
	{
		init_var(var);
		token = args->data;
		while (args && token->key != PIPE)
		{
			if (args && (token->key == RED_OUT || token->key == RED_INP
					|| token->key == RED_APP || token->key == HEREDOC))
			{
				handel_redere(&args, var, &token, env);
				if (var->heredoc && var->len > 0)
					var->heredoc_names[i++] = ft_strdup(var->file_name_herdoc);
			}
			else
				increment_args(&args, &token);
		}
		fill_cmd(cmd, *var, get_command1((*var).tmp, var), (*var).heredoc);
		if (args)
			skip_pipe(&args, &(*var).tmp, token);
	}
}

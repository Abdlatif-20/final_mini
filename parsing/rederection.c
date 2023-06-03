/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 01:21:27 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/03 18:55:12 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_cmd(t_list **cmd, t_var var, char **args, int heredoc)
{
	t_cmd	*cmds;

	cmds = NULL;
	cmds = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmds)
		return ;
		cmds->fd_in = var.fd_in;
		cmds->fd_out = var.fd_out;
		cmds->cmds = args;
		cmds->main_cmd = cmds->cmds[0];
		cmds->file_name = var.file_name;
		cmds->heredoc = heredoc;
	ft_lstadd_back(cmd, ft_lstnew(cmds));
}

void	rederection_app(t_list *args, int *fd_out)
{
	t_token	*token;

	token = args->data;
	if (token && token->key == RED_APP)
	{
		args = args->next;
		token = args->data;
		if (token && token->key == W_SPACE)
		{
			args = args->next;
			token = args->data;
		}
		if (token && token->key == RED_APP_FILE)
		{
			*fd_out = open(token->value, O_CREAT | O_RDWR | O_APPEND, 0777);
			args = args->next;
			if (args)
				token = args->data;
		}
		else
		{
			*fd_out = 404;
			printf("minishell: %s: ambiguous redirect\n", token->value);
			return ;
		}
	}
}

void	rederection_in(t_list *args, int *fd_in, char **file_name)
{
	t_token	*token;

	token = args->data;
	if (token && token->key == RED_INP)
	{
		args = args->next;
		if (args)
			token = args->data;
		if (token && token->key == W_SPACE)
		{
			args = args->next;
			if (args)
				token = args->data;
		}
		if (token && token->key == FILE_INP)
		{
			*fd_in = open(token->value, O_RDONLY);
			*file_name = token->value;
			args = args->next;
			if (args)
				token = args->data;
		}
		else
		{
			*fd_in = 404;
			printf("minishell: %s: ambiguous redirect\n", token->value);
			return ;
		}
	}
}

void	rederection_out(t_list *args, int *fd_out)
{
	t_token	*token;

	token = args->data;
	if (token && token->key == RED_OUT)
	{
		args = args->next;
		if (args)
			token = args->data;
		if (token && token->key == W_SPACE)
		{
			args = args->next;
			if (args)
				token = args->data;
		}
		if (token && token->key == RED_FILE)
		{
			if (token->value[0])
				*fd_out = open(token->value, O_CREAT | O_RDWR | O_TRUNC, 0777);
			args = args->next;
			if (args)
				token = args->data;
		}
		else
		{
			*fd_out = 404;
			printf("minishell: %s: ambiguous redirect\n", token->value);
			return ;
		}
	}
}

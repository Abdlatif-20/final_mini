/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntex_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 08:47:32 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/08 18:36:48 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_rederection(t_list **list, t_token *token, int *flag)
{
	if (token->key == HEREDOC || token->key == RED_OUT
		|| token->key == RED_APP || token->key == RED_INP)
	{
		(*list) = (*list)->next;
		if ((*list))
			token = (*list)->data;
		while ((*list) && token->key == W_SPACE)
		{
			(*list) = (*list)->next;
			if ((*list))
				token = (*list)->data;
		}
		if (!(*list))
			return (printf(ERR_NL), 1);
		if ((*list) && token->key == PIPE)
			return (printf(ERR_TK, token->value), 1);
		if ((*list) && token->key != EOFILE && token->key != RED_APP_FILE
			&& token->key != FILE_INP && token->key != RED_FILE
			&& token->key != SQUATES && token->key != DQUATES
			&& token->key != VAR)
			return (g_shell.exit_status = 258, printf(ERR_TK, token->value), 1);
			*flag = 1;
	}
	return (0);
}

int	check_pipes(t_list **list, t_token *token, int *flag)
{
	if ((*list) && token->key == PIPE && token->flag_quote == 0)
	{
		(*list) = (*list)->next;
		if ((*list))
			token = (*list)->data;
		while ((*list) && token->key == W_SPACE)
		{
			(*list) = (*list)->next;
			if ((*list))
				token = (*list)->data;
		}
		if (!(*list) || token->key == PIPE)
		{
			return (g_shell.exit_status = 258, printf(ERR_UNX_TNKN), 1);
		}
		else
			return (2);
			*flag = 1;
	}
	return (0);
}

int	syntex_error(t_list *list)
{
	int		flag;
	int		pipe_error;
	t_token	*token;

	flag = 0;
	token = NULL;
	while (list)
	{
		token = list->data;
		if (list && token->key == PIPE && !flag)
			return (g_shell.exit_status = 258, printf(ERR_UNX_TNKN), 1);
		if (list && check_rederection(&list, token, &flag))
			return (1);
		pipe_error = check_pipes(&list, token, &flag);
		if (pipe_error == 1)
			return (1);
		else if (pipe_error == 2)
			continue ;
		else
			flag = 1;
		list = list->next;
	}
	return (0);
}

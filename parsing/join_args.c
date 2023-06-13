/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:43:15 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/12 16:39:18 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	join_helper(t_list **args, t_token *tokens, char **token)
{
	if (tokens && tokens->key != W_SPACE && (tokens->key == SQUATES
			|| tokens->key == DQUATES || tokens->key == VAR
			|| tokens->key == WORD || tokens->key == FLAG
			|| tokens->key == RED_FILE || tokens->key == FILE_INP
			|| tokens->key == RED_APP_FILE || tokens->key == EOFILE))
	{
		*token = tokens->value;
		if ((*args)->next)
			tokens = (*args)->next->data;
		if (tokens && tokens->key != W_SPACE && (tokens->key == SQUATES
				|| tokens->key == DQUATES || tokens->key == VAR
				|| tokens->key == WORD || tokens->key == FLAG))
		{
			*token = ft_strjoin(*token, tokens->value);
			free(tokens->value);
			free(tokens);
			((t_token *)((*args)->data))->value = *token;
			ft_remove_node(args, (*args)->next);
			if ((*args))
				tokens = (*args)->data;
		}
		else
			(*args) = (*args)->next;
	}
}

void	ft_join_args(t_list **args)
{
	t_list	*tmp;
	t_token	*list;
	char	*token;

	tmp = *args;
	while (tmp && tmp->next != NULL)
	{
		token = NULL;
		list = tmp->data;
		if (list && list->key != W_SPACE && (list->key == SQUATES
				|| list->key == DQUATES || list->key == VAR || list->key == WORD
				|| list->key == FLAG || list->key == RED_FILE
				|| list->key == FILE_INP || list->key == RED_APP_FILE
				|| list->key == EOFILE))
			join_helper(&tmp, list, &token);
		else
			tmp = tmp->next;
	}
}

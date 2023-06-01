/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_command_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:40:27 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/31 17:00:23 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	helper_allocate(t_list **args, t_token *token, t_var *var)
{
	if (token->key == RED_APP || token->key == RED_INP
		|| token->key == RED_OUT || token->key == HEREDOC)
	{
			var->flag = 1;
			(*args) = (*args)->next;
	}
	else if (token->key == W_SPACE)
	{
		(*args) = (*args)->next;
		token = (*args)->data;
	}
	else if (token->key == WORD || token->key == FLAG
		|| token->key == SQUATES || token->key == DQUATES
		|| token->key == VAR)
	{
		if (!var->flag)
			var->i++;
		(*args) = (*args)->next;
		var->flag = 0;
	}
}

int	allocate_commande(t_list *args)
{
	t_token	*token;
	t_var	var;

	var.i = 0;
	var.flag = 0;
	while (args)
	{
		token = args->data;
		if (token->key == PIPE)
			break ;
		if (token->key == RED_APP || token->key == RED_INP
			|| token->key == RED_OUT || token->key == HEREDOC
			|| token->key == WORD || token->key == FLAG
			|| token->key == SQUATES || token->key == DQUATES
			|| token->key == VAR)
			helper_allocate(&args, token, &var);
		else
		{
			args = args->next;
			var.flag = 0;
		}
	}
	return (var.i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:30:35 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/01 09:29:26 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	trim_quotes_helper(char *tmp, t_var *var)
{
	if (var->string[var->i] == '\'')
	{
		var->i++;
		while (var->string[var->i] != '\'')
			tmp[var->j++] = var->string[var->i++];
	}
	else if (var->string[var->i] == '\"')
	{
		var->i++;
		while (var->string[var->i] != '\"')
			tmp[var->j++] = var->string[var->i++];
	}
	else
		tmp[var->j++] = var->string[var->i];
}

void	ft_trim_quotes(t_list **args)
{
	t_list	*current;
	char	*tmp;
	t_var	var;

	current = *args;
	while (current)
	{
		var.i = 0;
		var.j = 0;
		var.string = ((t_token *)(current->data))->value;
		tmp = malloc(ft_strlen(var.string) + 1);
		while (var.string[var.i])
		{
			trim_quotes_helper(tmp, &var);
			var.i++;
		}
		tmp[var.j] = '\0';
		free(((t_token *)(current->data))->value);
		((t_token *)(current->data))->value = tmp;
		current = current->next;
	}
}

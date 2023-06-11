/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 22:56:46 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/11 13:47:08 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	check_dquotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

void	free_token_list(t_list **list)
{
	t_list	*tmp;
	t_token	*token;

	while ((*list))
	{
		token = (*list)->data;
		tmp = (*list)->next;
		if (token->value)
			free(token->value);
		free((*list)->data);
		free((*list));
		(*list) = tmp;
	}
}

void	free_list_cmd(t_list **list)
{
	t_list	*tmp;
	t_cmd	*token;

	while ((*list))
	{
		token = (*list)->data;
		tmp = (*list)->next;
		if (token->cmds)
		{
			free(token->main_cmd);
			free(token->cmds);
			token->cmds = NULL;
		}
		free((*list)->data);
		free((*list));
		(*list) = tmp;
	}
}


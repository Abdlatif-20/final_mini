/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 22:56:46 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/14 01:14:46 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	check_sig(t_var *var)
{
	if (!var->input[0] && g_shell.signel_hedoc == 1)
	{
		rl_done = 0;
		free(var->input);
		return (1);
	}
	return (0);
}

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

	while ((*list))
	{
		tmp = (*list)->next;
		if (((t_token *)(*list)->data)->value)
			free(((t_token *)(*list)->data)->value);
		free((*list)->data);
		free((*list));
		(*list) = tmp;
	}
	(*list) = NULL;
}

void	free_list_cmd(t_list **list)
{
	t_list	*tmp;

	while ((*list))
	{
		tmp = (*list)->next;
		free_array(((t_cmd *)(*list)->data)->cmds);
		ft_free(((t_cmd *)(*list)->data)->file_name);
		((t_cmd *)(*list)->data)->cmds = NULL;
		free((*list)->data);
		free((*list));
		(*list) = tmp;
	}
}


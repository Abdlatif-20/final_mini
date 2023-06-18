/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:39:07 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/17 22:03:02 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	check_empty(t_var *var)
{
	if (var->is_empty_str)
		var->flag_bultin = 1;
}

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
		if (str[i] == '\"' || str[i] == '\'')
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

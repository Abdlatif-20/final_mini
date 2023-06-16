/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 22:56:46 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/16 21:33:36 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	check_sig(t_var *var)
{
	if (!var->input[0] && g_shell.signel_hedoc == 1)
	{
		// rl_done = 0;
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


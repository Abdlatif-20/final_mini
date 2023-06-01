/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:02:38 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/27 01:55:51 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] != '\'')
				return (1);
		}
		else if (input[i] == '\"')
		{
			i++;
			while (input[i] && input[i] != '\"')
				i++;
			if (input[i] != '\"')
				return (1);
		}
		if (input[i])
			i++;
	}
	return (0);
}

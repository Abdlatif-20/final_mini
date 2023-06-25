/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.ma>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:48:59 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/25 03:44:42 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	red_out(char *input, int *i, int *flag)
{
	int	len;

		len = 0;
	if (input[(*i) + len] == '$')
		*flag = 1;
	while (input[(*i) + len] && !ft_whitespace(input[(*i) + len])
		&& input[(*i) + len] != '\"' && input[(*i) + len] != '\''
		&& input[(*i) + len] != '<' && input[(*i) + len] != '>'
		&& input[(*i) + len] != '|')
			len++;
	return (len);
}

int	red_in(char *input, int *i, int *flag)
{
	int	len;

		len = 0;
	if (input[(*i) + len] == '$')
		*flag = 1;
	while (input[(*i) + len] && !ft_whitespace(input[(*i) + len])
		&& input[(*i) + len] != '\"' && input[(*i) + len] != '\''
		&& input[(*i) + len] != '<' && input[(*i) + len] != '>'
		&& input[(*i) + len] != '|')
			len++;
	return (len);
}

int	red_app(char *input, int *i, int *flag)
{
	int	len;

		len = 0;
	if (input[(*i) + len] == '$')
		*flag = 1;
	while (input[(*i) + len] && !ft_whitespace(input[(*i) + len])
		&& input[(*i) + len] != '\"' && input[(*i) + len] != '\''
		&& input[(*i) + len] != '<' && input[(*i) + len] != '>'
		&& input[(*i) + len] != '|')
			len++;
	return (len);
}

int	red_heredoc(char *input, int *i)
{
	int	len;

	len = 0;
	while (input[(*i) + len] && input[(*i) + len] != '\''
		&& input[(*i) + len] != '\"' && input[(*i) + len] != '<'
		&& input[(*i) + len] != '>' && input[(*i) + len] != '|'
		&& !ft_whitespace(input[(*i) + len]))
		len++;
	return (len);
}

int	delemeter_quotes(char *str, int *i, char c, int *flag)
{
	int	j;

	j = 1;
	while (str[(*i) + j] && str[(*i) + j] != c)
	{
		if (str[(*i) + j] == '$')
			*flag = 1;
		j++;
	}
	return (++j);
}

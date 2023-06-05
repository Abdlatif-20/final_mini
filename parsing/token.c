/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 22:55:34 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/05 21:14:21 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_word(char *input, t_list **token, t_var *var, int len)
{
	if (input[var->i] && !ft_whitespace(input[var->i]) && input[var->i] != '\"'
		&& input[var->i] != '\'' && input[var->i] != '<' && input[var->i] != '>'
		&& input[var->i] != '|' && input[var->i] != '$' && var->flag
		&& input[var->i] != '-')
	{
		len = 0;
		while (input[var->i + len] && input[var->i + len] != '-'
			&& !ft_whitespace(input[var->i + len])
			&& input[var->i + len] != '\"' && input[var->i + len] != '\''
			&& input[var->i + len] != '<' && input[var->i + len] != '>'
			&& input[var->i + len] != '$' && input[var->i + len] != '|')
				len++;
		if (len > 0 && var->flag)
		{
			fill_token(token, WORD, ft_substr(input, var->i, len), 0);
			var->flag = 0;
		}
		var->i += len;
		len = 0;
		while (input[var->i + len] && ft_whitespace(input[var->i + len]), 0)
			len++;
		if (len > 0)
			fill_token(token, W_SPACE, ft_substr(input, var->i, len), 0);
		var->i += len;
	}
}

void	check_pipe(char *input, t_list **token, int *i, int *flag)
{
	int	len;

	if (input[*i] && input[*i] == '|')
	{
		len = 0;
		while (input[(*i) + len] && ft_whitespace(input[(*i) + len]))
			len++;
		if (len > 0)
			fill_token(token, W_SPACE, ft_substr(input, (*i), len), 0);
		(*i) += len;
		len = 0;
		while (input[(*i) + len] && input[(*i) + len] == '|'
			&& !ft_whitespace(input[(*i) + len]))
			len++;
		fill_token(token, PIPE, ft_substr(input, (*i), len), 0);
		(*i) += len;
		*flag = 1;
	}
}

void	get_flags(char *input, t_list **token, t_var *var)
{
	int	len;

	if ((input[var->i] && input[var->i] != '\''
			&& !ft_whitespace(input[var->i]) && input[var->i] != '|'
			&& input[var->i] != '\"' && input[var->i] != '<'
			&& input[var->i] != '>' && input[var->i] != '$'
			&& !var->flag) || input[var->i] == '-')
	{
		len = 0;
		while (input[var->i + len] && input[var->i + len] != ' '
			&& input[var->i + len] != '\'' && input[var->i + len] != '\"'
			&& input[var->i + len] != '<' && input[var->i + len] != '>'
			&& input[var->i + len] != '$' && input[var->i + len] != '|')
			len++;
		if (len > 0)
			fill_token(token, FLAG, ft_substr(input, var->i, len), 0);
		var->i += len;
	}
}

void	check_quote(char *input, t_list **token, int *i, int len)
{
	if (input[(*i)] && ft_whitespace(input[(*i)]))
	{
		len = 0;
		while (input[(*i) + len] && ft_whitespace(input[(*i) + len]))
			len++;
		if (len > 0)
			fill_token(token, W_SPACE, ft_substr(input, (*i), len), 0);
		(*i) += len;
	}
	else if (input[(*i)] && input[(*i)] == '\"')
	{
		len = 1;
		while (input[(*i) + len] && input[(*i) + len] != '\"')
			len++;
		if (len > 0)
			fill_token(token, DQUATES, ft_substr(input, (*i), len + 1), 0);
		(*i) += len + 1;
	}
	else if (input[(*i)] && input[(*i)] == '\'')
	{
		len = 1;
		while (input[(*i) + len] && input[(*i) + len] != '\'')
			len++;
		if (len > 0)
			fill_token(token, SQUATES, ft_substr(input, (*i), len + 1), 0);
		(*i) += len + 1;
	}
}

void	check_variable(char *input, t_list **token, int *i)
{
	int	len;

	if (input[(*i)] && input[(*i)] == '$')
	{
		len = 1;
		while (input[(*i) + len] && !ft_whitespace(input[(*i) + len])
			&& input[(*i) + len] != '$'
			&& !ft_strchr(CHECK_SYMBOL, input[(*i) + len])
			&& input[(*i) + len] != '\'' && input[(*i) + len] != '\"'
			&& input[(*i) + len] != '|' && input[(*i) + len] != '<'
			&& input[(*i) + len] != '>')
			len++;
		if (len > 0)
			fill_token(token, VAR, ft_substr(input, (*i), len), 0);
		(*i) += len;
	}
}

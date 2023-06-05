/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:29:42 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/05 20:56:15 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_red_out(char *input, t_list **token, int *i)
{
	int	len;

	if (input[(*i)] && input[(*i)] == '>' && input[(*i) + 1] != '>')
	{
		fill_token(token, RED_OUT, ft_substr(input, (*i), 1), 0);
		len = 0;
		(*i) += 1;
		while (input[(*i) + len] && ft_whitespace(input[(*i) + len]))
			len++;
		if (len > 0)
			fill_token(token, W_SPACE, ft_substr(input, (*i), len), 0);
		(*i) += len;
		len = 0;
		while (input[(*i) + len] && !ft_whitespace(input[(*i) + len])
			&& input[(*i) + len] != '\"' && input[(*i) + len] != '\''
			&& input[(*i) + len] != '<' && input[(*i) + len] != '>'
			&& input[(*i) + len] != '|' && input[(*i) + len] != '$')
				len++;
		if (len > 0)
			fill_token(token, RED_FILE, ft_substr(input, (*i), len), 0);
		(*i) += len;
	}
}

void	check_red_in(char *input, t_list **token, int *i)
{
	int	len;

	if (input[(*i)] && input[(*i)] == '<' && input[(*i) + 1] != '<')
	{
		fill_token(token, RED_INP, ft_substr(input, (*i), 1), 0);
		len = 0;
		(*i) += 1;
		while (input[(*i) + len] && ft_whitespace(input[(*i) + len]))
			len++;
		if (len > 0)
			fill_token(token, W_SPACE, ft_substr(input, (*i), len), 0);
		(*i) += len;
		len = 0;
		while (input[(*i) + len] && !ft_whitespace(input[(*i) + len])
			&& input[(*i) + len] != '\"' && input[(*i) + len] != '\''
			&& input[(*i) + len] != '<' && input[(*i) + len] != '>'
			&& input[(*i) + len] != '|' && input[(*i) + len] != '$')
			len++;
		if (len > 0)
			fill_token(token, FILE_INP, ft_substr(input, (*i), len), 0);
		(*i) += len;
	}	
}

void	check_red_app(char *input, t_list **token, int *i)
{
	int	len;

	if (input[(*i)] && input[(*i)] == '>' && input[(*i) + 1] == '>')
	{
		fill_token(token, RED_APP, ft_substr(input, (*i), 2), 0);
		len = 0;
		(*i) += 2;
		while (input[(*i) + len] && ft_whitespace(input[(*i) + len]))
			len++;
		if (len > 0)
			fill_token(token, W_SPACE, ft_substr(input, (*i), len), 0);
		(*i) += len;
		len = 0;
		while (input[(*i) + len] && !ft_whitespace(input[(*i) + len])
			&& input[(*i) + len] != '\"' && input[(*i) + len] != '\''
			&& input[(*i) + len] != '<' && input[(*i) + len] != '>'
			&& input[(*i) + len] != '|' && input[(*i) + len] != '$'
			&& ft_isalnum(input[(*i) + len]))
			len++;
		if (len > 0)
			fill_token(token, RED_APP_FILE, ft_substr(input, (*i), len), 0);
		(*i) += len;
	}
}

void	check_red_heredoc(char *input, t_list **token, int *i)
{
	int	len;

	if (input[(*i)] && input[(*i)] == '<' && input[(*i) + 1] == '<')
	{
		fill_token(token, HEREDOC, ft_substr(input, (*i), 2), 1);
		len = 0;
		(*i) += 2;
		while (input[(*i) + len] && ft_whitespace(input[(*i) + len]))
			len++;
		if (len > 0)
			fill_token(token, W_SPACE, ft_substr(input, (*i), len), 1);
		(*i) += len;
		len = 0;
		while (input[(*i) + len] && !ft_whitespace(input[(*i) + len])
			&& input[(*i) + len] != '<' && input[(*i) + len] != '>'
			&& input[(*i) + len] != '|')
			len++;
		if (len > 0)
			fill_token(token, EOFILE, ft_substr(input, (*i), len), 1);
		(*i) += len;
	}
}

void	get_token(char *input, t_list **token)
{
	t_var	var;

	var.i = 0;
	var.flag = 1;
	input = skip_whitespace(input);
	while (input && input[var.i])
	{
		check_word(input, token, &var, 0);
		get_flags(input, token, &var);
		check_pipe(input, token, &var.i, &var.flag);
		check_quote(input, token, &var.i, 0);
		check_red_out(input, token, &var.i);
		check_red_in(input, token, &var.i);
		check_red_app(input, token, &var.i);
		check_red_heredoc(input, token, &var.i);
		check_variable(input, token, &var.i);
	}
	free(input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:54:13 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/14 01:24:09 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	handel_expand_heredoc(char *input, t_list **temp)
{
	int		len;
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (input[i] == '$')
	{
		len = 1;
		while (input[i + len] && !ft_whitespace(input[i + len])
			&& input[i + len] != '$'
			&& !ft_strchr(CHECK_SYMBOL, input[i + len])
			&& input[i + len] != '\'' && input[i + len] != '\"'
			&& input[i + len] != '|' && input[i + len] != '<'
			&& input[i + len] != '>')
			len++;
		tmp = ft_substr(input, i, len);
		i += len;
		fill_token(temp, VAR, tmp, 0);
		if (input[i] == '$')
			handel_expand_heredoc(input + i, temp);
	}
}

char	*get_value_heredoc(t_list *tmp, char *input)
{
	t_token	*token;

	input = NULL;
	while (tmp)
	{
		token = tmp->data;
		input = ft_strjoin(input, token->value);
		tmp = tmp->next;
	}
	return (input);
}

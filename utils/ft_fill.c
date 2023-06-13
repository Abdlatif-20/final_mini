/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 12:03:36 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/12 15:50:46 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_cmd(t_list **cmd, t_var var, char **args, int heredoc)
{
	t_cmd	*cmds;

	cmds = NULL;
	cmds = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmds)
		return ;
		cmds->fd_in = var.fd_in;
		cmds->fd_out = var.fd_out;
		cmds->cmds = args;
		args = NULL;
		cmds->main_cmd = cmds->cmds[0];
		cmds->file_name = var.file_name;
		cmds->heredoc = heredoc;
	ft_lstadd_back(cmd, ft_lstnew(cmds));
}

void	fill_token(t_list **args, int token, char *word, int is_heredoc)
{
	t_token	*tokens;

	tokens = NULL;
	if (word)
	{
		tokens = (t_token *)malloc(sizeof(t_token));
		if (!tokens)
			return ;
		tokens->value = word;
		if (token == DQUATES || check_dquotes(word))
		{
			tokens->key = token;
			tokens->flag_quote = 1;
		}
		else
		{
			tokens->key = token;
			tokens->flag_quote = 0;
		}
		tokens->is_herdoc = is_heredoc;
		ft_lstadd_back(args, ft_lstnew(tokens));
	}
}

void	fill_white_space(char *input, t_list **token, t_var **var)
{
	int	len;

	len = 0;
	while (input[(*var)->i + len] && ft_whitespace(input[(*var)->i + len]))
		len++;
	if (len > 0)
		fill_token(token, W_SPACE, ft_substr(input, (*var)->i, len), 0);
	(*var)->i += len;
}

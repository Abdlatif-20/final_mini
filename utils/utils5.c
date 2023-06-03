/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 22:56:46 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/03 19:36:39 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

void	fill_token(t_list **args, int token, char *word, int is_heredoc)
{
	t_token	*tokens;

	if (word)
	{
		tokens = (t_token *)malloc(sizeof(t_token));
		tokens->value = word;
		if (token == DQUATES)
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

char	*skip_whitespace(char *input)
{
	t_var	var;

	var.i = 0;
	var.start = 0;
	var.end = 0;
	var.string = NULL;
	while (input[var.i] && ft_whitespace(input[var.i]))
		var.i++;
	var.start = var.i;
	if (!input[var.i])
		return (NULL);
	var.len = ft_strlen(input) - 1;
	while (input[var.len] && ft_whitespace(input[var.len]))
		var.len--;
	if (var.len >= 0)
		var.end = var.len;
	if (var.start < var.end)
		var.string = malloc((var.end - var.start) + 2);
	else
		var.string = malloc((var.start - var.end) + 2);
	var.i = 0;
	while (input[var.start] && var.start <= var.end)
		var.string[var.i++] = input[var.start++];
	var.string[var.i] = '\0';
	return (var.string);
}

void	ft_remove_node(t_list **head, t_list *node)
{
	t_list	*tmp;
	t_list	*next_node;

	tmp = *head;
	if (tmp == NULL)
		return ;
	if (tmp == node)
	{
		*head = tmp->next;
		free (tmp);
		return ;
	}
	while (tmp->next && tmp->next != node)
		tmp = tmp->next;
	if (tmp->next == NULL)
		return ;
	next_node = tmp->next->next;
	free(tmp->next);
	tmp->next = next_node;
}

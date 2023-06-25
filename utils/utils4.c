/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.ma>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:31:32 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/25 02:20:13 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_var(t_var *var)
{
	var->heredoc = 0;
	var->fd_in = 0;
	var->fd_out = 1;
	var->file_name = NULL;
	var->file_heredoc = NULL;
	var->file_name_herdoc = NULL;
}

int	herdoc_count(t_list *args)
{
	t_token	*token;
	int		count;

	if (!args)
		return (-1);
	count = 0;
	while (args)
	{
		token = args->data;
		if (token->key == HEREDOC)
			count++;
		args = args->next;
	}
	return (count);
}

void	var_init(t_var *var, char *input)
{
	var->i = 0;
	var->start = 0;
	var->end = 0;
	var->string = NULL;
	var->len = ft_strlen(input) - 1;
}

char	*skip_whitespace(char *input)
{
	t_var	var;

	if (!input)
		return (NULL);
	var_init(&var, input);
	while (input[var.i] && ft_whitespace(input[var.i]))
		var.i++;
	var.start = var.i;
	if (!input[var.i])
		return (NULL);
	while (input[var.len] && ft_whitespace(input[var.len]))
		var.len--;
	if (var.len >= 0)
		var.end = var.len;
	if (var.start < var.end)
		var.string = malloc((var.end - var.start) + 2);
	else
		var.string = malloc((var.start - var.end) + 2);
	if (!var.string)
		return (NULL);
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

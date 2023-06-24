/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.ma>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:38:29 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/24 02:22:55 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_heredocs(char **array, int size)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return (free(array));
	while (i <= size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_token_list(t_list **list)
{
	t_list	*tmp;

	while ((*list))
	{
		tmp = (*list)->next;
		if (((t_token *)(*list)->data)->value)
			free(((t_token *)(*list)->data)->value);
		free((*list)->data);
		free((*list));
		(*list) = tmp;
	}
	(*list) = NULL;
}

void	free_list_cmd(t_list **list)
{
	t_list	*tmp;

	while ((*list))
	{
		tmp = (*list)->next;
		free_array(((t_cmd *)(*list)->data)->cmds);
		ft_free(((t_cmd *)(*list)->data)->file_name);
		((t_cmd *)(*list)->data)->cmds = NULL;
		free((*list)->data);
		free((*list));
		(*list) = tmp;
	}
}

void	unlink_heredoc(char **file_names, int size)
{
	int	i;

	if (!file_names)
		return ;
	i = 0;
	while (i < size)
	{
		unlink(file_names[i]);
		i++;
	}
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

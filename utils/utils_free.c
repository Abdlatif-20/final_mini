/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 03:56:40 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/17 15:42:01 by ahaloui          ###   ########.fr       */
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

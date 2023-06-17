/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:44:58 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/05 21:55:37 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*swap;

	if (*lst && lst)
	{
		while (*lst)
		{
			swap = (*lst)->next;
			free(*lst);
			(*lst) = swap;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:36:33 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/05 21:55:14 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*begg;
	int		index;

	begg = lst;
	index = 0;
	while (begg != NULL)
	{
		index++;
		begg = begg->next;
	}
	return (index);
}

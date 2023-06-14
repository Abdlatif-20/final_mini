/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:01:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/14 21:22:18 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_export	*ft_lst_new_export(char *export_var, char *export_value, int flag)
{
	t_export	*element;

	element = NULL;
	element = (t_export *)malloc(sizeof(t_export));
	if (element != NULL)
	{
		element->export_var = ft_strdup(export_var);
		element->export_value = ft_strdup(export_value);
		if (flag)
		{
			free(export_var);
			free(export_value);
		}
		element->next = NULL;
	}
	return (element);
}

void	ft_lst_add_back_export(t_export **lst, t_export *new)
{
	t_export	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		// free(new->export_value);
		// free(new->export_var);
		return ;
	}
	else
	{
		tmp = *lst;
		while ((*lst)->next != NULL)
			(*lst) = (*lst)->next;
		(*lst)->next = new;
		(*lst) = tmp;
	}
	// free(new->export_value);
	// free(new->export_var);
}

void	add_export_element(char *export_var, char *export_value,
	t_export **head_ex)
{
	t_export	*new;

	new = ft_lst_new_export(export_var, export_value, 0);
	ft_lst_add_back_export(head_ex, new);
}


void	print_list_export(t_info *info)
{
	t_export	*tmp;

	sort_export_list(&info->head_ex);
	tmp = info->head_ex;
	while (tmp)
	{
		if (!tmp->export_value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->export_var, 1);
			ft_putstr_fd("\n", 1);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->export_var, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->export_value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		tmp = tmp->next;
	}
}

void	sort_export_list(t_export **head_ex)
{
	t_export	*tmp;
	t_export	*tmp2;
	char		*tmp_name;
	char		*tmp_value;

	tmp = *head_ex;
	if (!head_ex || !*head_ex || tmp)
		return ;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->export_var, tmp2->export_var) > 0)
			{
				tmp_name = tmp->export_var;
				tmp_value = tmp->export_value;
				tmp->export_var = tmp2->export_var;
				tmp->export_value = tmp2->export_value;
				tmp2->export_var = tmp_name;
				tmp2->export_value = tmp_value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:01:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/15 02:02:49 by ahaloui          ###   ########.fr       */
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
	t_export	*prev;
	t_export	*suivant;
	char		*tmp_var;
	char		*tmp_value;

	prev = *head_ex;
	while (prev)
	{
		suivant = prev->next;
		while (suivant)
		{
			if (ft_strcmp(prev->export_var, suivant->export_var) > 0)
			{
				tmp_var = prev->export_var;
				tmp_value = prev->export_value;
				prev->export_var = suivant->export_var;
				prev->export_value = suivant->export_value;
				suivant->export_var = tmp_var;
				suivant->export_value = tmp_value;
			}
			suivant = suivant->next;
		}
		prev = prev->next;
	}
}

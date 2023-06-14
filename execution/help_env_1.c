/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_env_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:39:17 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/14 15:33:01 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_lst_new_env(char *env_var, char *env_value, int flag)
{
	t_env	*element;

	element = NULL;
	element = (t_env *)malloc(sizeof(t_env));
	if (element != NULL)
	{
		element->env_var = ft_strdup(env_var);
		element->env_value = ft_strdup(env_value);
		element->next = NULL;
		if (flag)
		{
			free(env_var);
			free(env_value);
		}
	}
	return (element);
}

void	ft_lst_add_back_env(t_env **head_en, t_env *new)
{
	t_env	*tmp;

	if (*head_en == NULL)
	{
		*head_en = new;
		return ;
	}
	else
	{
		tmp = *head_en;
		while ((*head_en)->next != NULL)
			(*head_en) = (*head_en)->next;
		(*head_en)->next = new;
		(*head_en) = tmp;
	}
}

void	remove_env_element(t_env **head_en, char *env_var)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *head_en;
	if (tmp != NULL && !ft_strcmp(tmp->env_var, env_var))
	{
		*head_en = tmp->next;
		free(tmp->env_value);
		free(tmp->env_var);
		free(tmp);
		return ;
	}
	while (tmp != NULL && ft_strcmp(tmp->env_var, env_var) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free(tmp->env_value);
	free(tmp->env_var);
	free(tmp);
}

void	add_env_element(char *env_var, char *env_value, t_env **head_en)
{
	t_env	*new;

	new = ft_lst_new_env(env_var, env_value, 0);
	ft_lst_add_back_env(head_en, new);
}

void	print_list_env(t_info *info)
{
	t_env	*head_en;

	head_en = info->head_en;
	while (head_en != NULL)
	{
		if (head_en->env_value != NULL)
			printf("%s=%s\n", head_en->env_var, head_en->env_value);
		head_en = head_en->next;
	}
}

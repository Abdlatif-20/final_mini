/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_env_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:39:17 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/20 04:30:45 by ahaloui          ###   ########.fr       */
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
	t_env	*prev;
	t_env	*suivant;

	prev = *head_en;
	if (!ft_strcmp(prev->env_var, env_var))
	{
		*head_en = prev->next;
		free(prev->env_value);
		free(prev->env_var);
		free(prev);
		return ;
	}
	while (prev)
	{
		suivant = prev->next;
		if (suivant && !ft_strcmp(suivant->env_var, env_var))
		{
			prev->next = suivant->next;
			free(suivant->env_value);
			free(suivant->env_var);
			free(suivant);
			return ;
		}
		prev = prev->next;
	}
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
		if (!ft_strcmp("HOME", head_en->env_var) && info->var->flag_home)
		{
			head_en = head_en->next;
			continue ;
		}
		if ((!ft_strcmp("PATH", head_en->env_var)
				&& info->var->flag_path_ignored)
			|| (!ft_strcmp("OLDPWD", head_en->env_var)
				&& info->var->flag_oldpwd))
		{
			head_en = head_en->next;
			continue ;
		}
		if (head_en->env_value != NULL)
		{
			ft_putstr_fd(head_en->env_var, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(head_en->env_value, 1);
			ft_putstr_fd("\n", 1);
		}
		head_en = head_en->next;
	}
}

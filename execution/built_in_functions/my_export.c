/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:40:52 by ahaloui           #+#    #+#             */
/*   Updated: 2023/05/30 23:38:48 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_export	*ft_lst_new_export(char *export_var, char *export_value)
{
	t_export	*element;

	element = NULL;
	element = (t_export *)malloc(sizeof(t_export));
	if (element != NULL)
	{
		element->export_var = export_var;
		element->export_value = export_value;
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

char *get_export_variable(char *variable)
{
	int i;
	char *env_variable;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	env_variable = ft_substr(variable, 0, i);
	return (env_variable);
}

char *get_export_value(char *value)
{
	int i;
	char *env_value;

	i = 0;
	while (value[i] && value[i] != '=')
		i++;
	if (!ft_strchr(value, '='))
		return (NULL);
	env_value = ft_substr(value, i + 1, ft_strlen(value) - i);
	return (env_value);
}

void add_export_element(char *export_var, char *export_value, t_export **head_ex)
{
	t_export *new;
	new = ft_lst_new_export(export_var, export_value);
	ft_lst_add_back_export(head_ex, new);
}
void print_list_export(t_info *info)
{
	t_export *tmp;
	sort_export_list(&info->head_ex);

	tmp = info->head_ex;
	while (tmp)
	{
		if (!tmp->export_value)
		{
			// printf("declare -x %s\n", tmp->export_var);
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->export_var, 1);
			ft_putstr_fd("\n", 1);

		}
		else
		{
			// printf("declare -x %s=\"%s\"\n", tmp->export_var, tmp->export_value);
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->export_var, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->export_value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		tmp = tmp->next;
	}
}
void sort_export_list(t_export **head_ex)
{
	t_export *tmp;
	t_export *tmp2;
	char *tmp_name;
	char *tmp_value;

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
int check_is_empty_string(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int check_if_export_var_exist(t_export *head_ex, char *export_var)
{
	while (head_ex)
	{
		if (ft_strcmp(head_ex->export_var, export_var) == 0)
			return (1);
		head_ex = head_ex->next;
	}
	return (0);
}

void remove_export_element(t_export **head_ex, char *export_var)
{
	t_export *tmp;
	t_export *tmp2;

	tmp = *head_ex;
	if (!ft_strcmp(tmp->export_var, export_var))
	{
		*head_ex = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp2 && !ft_strcmp(tmp2->export_var, export_var))
		{
			tmp->next = tmp2->next;
			free(tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}
void fill_export_list(char **environ, t_export **head_ex)
{
	int i = 0;
	char *export_var;
	char *export_value;

	while (environ[i])
	{
		export_var = get_export_variable(environ[i]);
		export_value = get_export_value(environ[i]);
		add_export_element(export_var, export_value, head_ex);
		i++;
	}
	if ((*head_ex) && head_ex)
	{
		sort_export_list(head_ex);
	}
}


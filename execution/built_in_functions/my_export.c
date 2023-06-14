/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:40:52 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/14 00:01:30 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_export_variable(char *variable)
{
	int		i;
	char	*env_variable;

	i = 0;
	if (!variable)
		return (NULL);
	while (variable[i] && variable[i] != '=')
		i++;
	env_variable = ft_substr(variable, 0, i);
	return (env_variable);
}

char	*get_export_value(char *value)
{
	int		i;
	char	*env_value;

	i = 0;
	env_value = NULL;
	while (value[i] && value[i] != '=')
		i++;
	if (!ft_strchr(value, '='))
		return (NULL);
	env_value = ft_substr(value, i + 1, ft_strlen(value) - i);
	return (env_value);
}

int	check_if_export_var_exist(t_export *head_ex, char *export_var)
{
	while (head_ex)
	{
		if (ft_strcmp(head_ex->export_var, export_var) == 0)
			return (1);
		head_ex = head_ex->next;
	}
	return (0);
}

void	remove_export_element(t_export **head_ex, char *export_var)
{
	t_export	*tmp;
	t_export	*tmp2;

	tmp = *head_ex;
	if (!ft_strcmp(tmp->export_var, export_var))
	{
		*head_ex = tmp->next;
		free(tmp->export_value);
		free(tmp->export_var);
		free(tmp);
		return ;
	}
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp2 && !ft_strcmp(tmp2->export_var, export_var))
		{
			tmp->next = tmp2->next;
			free(tmp2->export_value);
			free(tmp2->export_var);
			free(tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}

void	fill_export_list(char **environ, t_export **head_ex)
{
	int		i;
	char	*export_var;
	char	*export_value;

	i = 0;
	export_var = NULL;
	export_value = NULL;
	while (environ[i])
	{
		export_var = get_export_variable(environ[i]);
		export_value = get_export_value(environ[i]);
		add_export_element(export_var, export_value, head_ex);
		free(export_var);
		free(export_value);
		i++;
	}
	if ((*head_ex) && head_ex)
		sort_export_list(head_ex);
}

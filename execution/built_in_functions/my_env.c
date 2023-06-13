/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:42:13 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/13 23:59:16 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_variable(char *variable)
{
	int		i;
	char	*env_variable;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	env_variable = ft_substr(variable, 0, i);
	return (env_variable);
}

char	*get_env_value(char *value)
{
	int		i;
	char	*env_value;

	i = 0;
	while (value[i] && value[i] != '=')
		i++;
	if (!ft_strchr(value, '='))
		return (NULL);
	env_value = ft_substr(value, i + 1, ft_strlen(value) - i);
	return (env_value);
}

int	check_is_empty_string_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_if_env_var_exist(t_env *head_en, char *env_var)
{
	while (head_en)
	{
		if (ft_strcmp(head_en->env_var, env_var) == 0)
			return (1);
		head_en = head_en->next;
	}
	return (0);
}

void	fill_env_list(char **environ, t_env **head_env)
{
	int		i;
	char	*env_variable;
	char	*env_value;

	i = 0;
	env_variable = NULL;
	env_value = NULL;
	while (environ[i])
	{
		env_variable = get_env_variable(environ[i]);
		env_value = get_env_value(environ[i]);
		add_env_element(env_variable, env_value, head_env);
		free(env_variable);
		free(env_value);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:25:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/18 21:00:53 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	concatenation_env(t_env **head_en, char *env_var, char *new_value)
{
	t_env	*tmp;

	tmp = *head_en;
	while (tmp)
	{
		if (!ft_strcmp(tmp->env_var, env_var))
			tmp->env_value = ft_strjoin(tmp->env_value, new_value);
		tmp = tmp->next;
	}
}

int	help_env1(t_env **head_en, char *env_variable,
	char *env_value, int concatenate)
{
	if (check_if_env_var_exist(*head_en, env_variable))
	{
		if (concatenate == 1)
		{
			concatenation_env(head_en, env_variable, env_value);
			return (1);
		}
		else
			remove_env_element(head_en, env_variable);
	}
	return (0);
}

void	process_env_argument(t_env **head_en, char *arg)
{
	char	*env_variable;
	char	*env_value;
	int		concatenate;

	env_variable = get_env_variable(arg);
	env_value = get_env_value(arg);
	concatenate = 0;
	if (env_variable[ft_strlen(env_variable) - 1] == '+')
	{
		if (env_variable[ft_strlen(env_variable) - 2] == '+')
		{
			g_shell.exit_status = EXIT_FAILURE;
			return (free(env_variable), free(env_value));
		}
		concatenate = 1;
		env_variable[ft_strlen(env_variable) - 1] = '\0';
	}
	if (help_env1(head_en, env_variable, env_value, concatenate))
		return (free(env_variable), free(env_value));
	add_env_element(env_variable, env_value, head_en);
	free(env_variable);
	free(env_value);
}

void	add_env(t_env **head_en, char **split, t_info *info)
{
	int		i;
	char	*arg;

	i = 1;
	while (split[i])
	{
		arg = get_arg(split[i]);
		printf("arg = %s  | flag_home = %d\n", arg, info->var->flag_home);
		if (!ft_strcmp("HOME=", arg) && info->var->flag_home == 1)
			info->var->flag_home = 0;
		if (split[i][0] == '\0' || check_if_valid_args(arg) == 0)
		{
			free(arg);
			i++;
			continue ;
		}
		process_env_argument(head_en, split[i]);
		free(arg);
		i++;
	}
}

void	free_env(t_env **head_en)
{
	t_env	*tmp;

	while (*head_en)
	{
		tmp = *head_en;
		*head_en = (*head_en)->next;
		free(tmp->env_var);
		free(tmp->env_value);
		free(tmp);
	}
}

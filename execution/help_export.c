/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:54:57 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/20 18:25:37 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	concatenation_export(t_export **head_ex,
	char *export_variable, char *new_value)
{
	t_export	*tmp;

	tmp = *head_ex;
	while (tmp)
	{
		if (!ft_strcmp(tmp->export_var, export_variable))
			tmp->export_value = ft_strjoin(tmp->export_value, new_value);
		tmp = tmp->next;
	}
}

int	help_export1(t_export **head_ex, char *export_variable,
	char *export_value, int concatenate)
{
	if (check_if_export_var_exist(*head_ex, export_variable))
	{
		if (concatenate == 1)
		{
			concatenation_export(head_ex, export_variable, export_value);
			return (1);
		}
		else
			remove_export_element(head_ex, export_variable);
	}
	return (0);
}

void	process_export_argument(t_export **head_ex, char *arg)
{
	char	*export_variable;
	char	*export_value;
	int		concatenate;

	export_variable = get_export_variable(arg);
	export_value = get_export_value(arg);
	concatenate = 0;
	if (export_variable[ft_strlen(export_variable) - 1] == '+')
	{
		if (export_variable[ft_strlen(export_variable) - 2] == '+')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_shell.exit_status = EXIT_FAILURE;
			return (free(export_variable), free(export_value));
		}
		concatenate = 1;
		export_variable[ft_strlen(export_variable) - 1] = '\0';
	}
	if (help_export1(head_ex, export_variable, export_value, concatenate))
		return (free(export_variable), free(export_value));
	add_export_element(export_variable, export_value, head_ex);
	free(export_variable);
	free(export_value);
}

void	add_export(t_export **head_ex, char **split, t_info *info)
{
	int		i;
	char	*arg;

	i = 1;
	while (split[i])
	{
		arg = get_arg(split[i]);
		if (!ft_strcmp("HOME=", arg) && info->var->flag_home == 1)
			info->var->flag_home = 0;
		if (split[i][0] == '\0' || check_if_valid_args(arg) == 0)
		{
			free(arg);
			i++;
			continue ;
		}
		process_export_argument(head_ex, split[i]);
		free(arg);
		i++;
	}
}

void	free_export(t_export **head_ex)
{
	t_export	*tmp;

	while (*head_ex)
	{
		tmp = *head_ex;
		*head_ex = (*head_ex)->next;
		free(tmp->export_var);
		free(tmp->export_value);
		free(tmp);
	}
}

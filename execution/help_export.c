/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:54:57 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/09 23:54:59 by aben-nei         ###   ########.fr       */
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

void	help_export1(t_export **head_ex, char *export_variable,
	char *export_value, int concatenate)
{
	if (check_if_export_var_exist(*head_ex, export_variable))
	{
		if (concatenate == 1)
		{
			concatenation_export(head_ex, export_variable, export_value);
			return ;
		}
		else
			remove_export_element(head_ex, export_variable);
	}
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
			printf("minishell: export: `%s': not a valid identifier\n", arg);
			g_shell.exit_status = EXIT_FAILURE;
			return ;
		}
		concatenate = 1;
		export_variable[ft_strlen(export_variable) - 1] = '\0';
	}
	help_export1(head_ex, export_variable, export_value, concatenate);
	add_export_element(export_variable, export_value, head_ex);
}

void	add_export(t_export **head_ex, char **split)
{
	int	i;

	i = 1;
	while (split[i])
	{
		if (split[i][0] == '\0')
		{
			i++;
			continue ;
		}
		process_export_argument(head_ex, split[i]);
		i++;
	}
}

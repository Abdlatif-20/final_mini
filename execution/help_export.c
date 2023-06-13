/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:54:57 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/13 20:42:22 by ahaloui          ###   ########.fr       */
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
			return (1) ;
		}
		else
			remove_export_element(head_ex, export_variable);
	}
	return (0);
}

// void	process_export_argument(t_export **head_ex, char *arg)
// {
// 	char	*export_variable;
// 	char	*export_value;
// 	int		concatenate;

// 	export_variable = get_export_variable(arg);
// 	export_value = get_export_value(arg);
// 	concatenate = 0;
// 	if (export_variable[ft_strlen(export_variable) - 1] == '+')
// 	{
// 		if (export_variable[ft_strlen(export_variable) - 2] == '+')
// 		{
// 			printf("minishell: export: `%s': not a valid identifier\n", arg);
// 			g_shell.exit_status = EXIT_FAILURE;
// 			return ;
// 		}
// 		concatenate = 1;
// 		export_variable[ft_strlen(export_variable) - 1] = '\0';
// 	}
// 	if (help_export1(head_ex, export_variable, export_value, concatenate))
// 		return ;
// 	add_export_element(export_variable, export_value, head_ex);
// }

void add_export(t_export **head_ex, char **split)
{
	int i;
	char *export_variable;
	char *export_value;
	int concatenate;
 
	i = 1;
	while (split[i])
	{
		concatenate = 0;
		if (split[i][0] == '\0' || (check_if_valid_args(split[i]) == false))
		{
			i++;
			continue;        
		}
		export_value = get_export_value(split[i]);
		export_variable = get_export_variable(split[i]);
		if (export_variable[ft_strlen(export_variable) - 1] == '+')
		{
			concatenate = 1;
			export_variable[ft_strlen(export_variable) - 1] = '\0';
		}
		if (check_if_export_var_exist(*head_ex, export_variable))
		{
			if (concatenate == 1)
			{
				concatenation_export(head_ex, export_variable, export_value);
				i++;
				continue;
			}
			else
				remove_export_element(head_ex, export_variable);
		}
		add_export_element(export_variable, export_value, head_ex);
		i++;
	}
}

void free_export(t_export **head_ex)
{
	t_export *tmp;

	while (*head_ex)
	{
		tmp = *head_ex;
		*head_ex = (*head_ex)->next;
		free(tmp->export_var);
		free(tmp->export_value);
		free(tmp);
	}
}



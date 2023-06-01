/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:07:13 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/01 22:24:44 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int  check_export(char **split)
{
	int i;
	int valid;

	i = 1;
	valid = 1;
	while (split[i])
	{
		if (split[i][0] == '\0')
		{
			i++;
			continue;
		}
		if (check_if_valid_args(split[i]) == false)
			printf("minishell: export: `%s': not a valid identifier\n", split[i]);
		i++;
	}
	return (valid);
}
int check_if_valid_args(char *split)
{
	int i = 0;
	int b = 1;

	if (split[i] && split[i] == '\0')
		return (1);
	if (split[i] && !ft_isalpha(split[i]) && split[i] != '_')
	   return (0);
	i = i + 1;
	while (split[i])
	{
		if (!ft_isalnum(split[i]))
		{
			if (split[i] == '+' && split[i + 1] == '\0' )
				b = 0;
			else
			{
				if (split[i] == '\0')
					break;
				b = 1;
				break ;
			}
		}
		i++;
	}  
	return (b);
}

void    concatenation_export(t_export **head_ex,char *export_variable, char *new_value)
{
   t_export *tmp;
   
	tmp = *head_ex;
	while (tmp)
	{
		if (!ft_strcmp(tmp->export_var, export_variable))
			tmp->export_value = ft_strjoin(tmp->export_value, new_value);
		tmp = tmp->next;
	}
}

void handle_export_concatenation(t_export **head_ex, char *export_variable, char *export_value)
{
    export_variable[ft_strlen(export_variable) - 1] = '\0';
    if (!check_if_export_var_exist(*head_ex, export_variable))
        add_export_element(export_variable, export_value, head_ex);
    else
        concatenation_export(head_ex, export_variable, export_value);
}

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
			if (export_variable[ft_strlen(export_variable) - 2] == '+')
			{
				printf("minishell: export: `%s': not a valid identifier\n", split[i]);
				i++;
				continue;
			}
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
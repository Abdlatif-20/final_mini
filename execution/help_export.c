/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:07:13 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/08 22:02:37 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



// int is_valid_variable_first_char(int c)
// {
// 	if (ft_isalpha(c) || c == '_')
// 		return (1);
// 	return (0);
// }

// int is_valid_variable(char *str)
// {
// 	int i;

// 	i = 0;
// 	if (!is_valid_variable_first_char(str[i]))
// 		return (0);
// 	i++;
// 	while (str[i])
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '_' && str[ft_strlen(str) - 1] != '+')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

int check_if_valid_args(char *split)
{
	int i = 0;


	if (split[i] && split[i] == '\0')
		return (0);
	if (split[i] && !ft_isalpha(split[i]) && split[i] != '_')
	   return (0);
	i = i + 1;
	while (split[i])
	{
		if (ft_isalnum(split[i]) || split[i] == '_' || split[i] == '=')
		{
			i++;
			continue;
		}
		else if (split[i] == '+')
		{
			if (split[i + 1] == '\0')
				return (1);
			else
				return (0);
		}
		else 
			return (0);
		i++;
	}
	return (1);
}

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
		if (check_if_valid_args(get_export_variable(split[i])) == 0)
			printf("minishell: export: `%s': not a valid identifier\n", split[i]);
		i++;
	}
	return (valid);
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



void process_export_argument(t_export **head_ex, char *arg)
{
    char *export_variable = get_export_variable(arg);
	
    char *export_value = get_export_value(arg);
    int concatenate = 0;

    if (export_variable[ft_strlen(export_variable) - 1] == '+')
    {
        if (export_variable[ft_strlen(export_variable) - 2] == '+')
        {
            printf("minishell: export: `%s': not a valid identifier\n", arg);
			g_shell.exit_status = EXIT_FAILURE;
            return;
        }
        concatenate = 1;
        export_variable[ft_strlen(export_variable) - 1] = '\0';
    }
    
    if (check_if_export_var_exist(*head_ex, export_variable))
    {
        if (concatenate == 1)
        {
            concatenation_export(head_ex, export_variable, export_value);
            return;
        }
        else
            remove_export_element(head_ex, export_variable);
    }
    add_export_element(export_variable, export_value, head_ex);
}

void add_export(t_export **head_ex, char **split)
{
    int i = 1;
	
    while (split[i])
    {
        if (split[i][0] == '\0' || !check_if_valid_args(get_export_variable(split[i])))
        {
            i++;
            continue;
        }
        process_export_argument(head_ex, split[i]);
        i++;
    }
}


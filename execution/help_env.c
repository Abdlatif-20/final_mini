/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:25:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/07 00:45:28 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void concatenation_env(t_env **head_en, char *env_var, char *new_value)
{
   t_env *tmp;
   
    tmp = *head_en;
    while (tmp)
    {
        if (!ft_strcmp(tmp->env_var, env_var))
            tmp->env_value = ft_strjoin(tmp->env_value, new_value);
        tmp = tmp->next;
    }
}

// void add_env(t_env **head,  char **split)
// {
//     int i;
//     char *env_var;
//     char *env_value;
//     int concatenate;

//     i = 1;
//     while (split[i])
//     {
//         concatenate = 0;
//         if (split[i][0] == '\0' || (check_if_valid_args(split[i]) == false))
// 		{
// 			i++;
// 			continue;        
// 		}
//         env_value = get_env_value(split[i]);
//         env_var = get_env_variable(split[i]);
//         if (env_var[ft_strlen(env_var) - 1] == '+')
//         {
//             concatenate = 1;
//             env_var[ft_strlen(env_var) - 1] = '\0';
//         }
//         if (check_if_env_var_exist(*head, env_var))
//         {
//             if (concatenate == 1)
//             {
//                 concatenation_env(head, env_var, env_value);
//                 i++;
//                 continue;
//             }
//             else
//                 remove_env_element(head, env_var);
//         }
//         add_env_element(env_var, env_value, head);
//         i++;
//     }
// }

// void process_env_argument(t_env **head_en, char *arg)
// {
//     char *env_variable = get_env_variable(arg);
//     char *env_value = get_env_value(arg);
//     int concatenate = 0;
//     if (env_variable[ft_strlen(env_variable) - 1] == '+')
//     {
//         if (env_variable[ft_strlen(env_variable) - 2] == '+')
//         {
//             printf("minishell: env: `%s': not a valid identifier\n", arg);
// 			g_shell.exit_status = EXIT_FAILURE;
//             return;
//         }
//         concatenate = 1;
//         env_variable[ft_strlen(env_variable) - 1] = '\0';
//     }
    
//     if (check_if_env_var_exist(*head_en, env_variable))
//     {
//         if (concatenate == 1)
//         {
//             concatenation_env(head_en, env_variable, env_value);
//             return;
//         }
//         else
//             remove_env_element(head_en, env_variable);
//     }
//     add_env_element(env_variable, env_value, head_en);
// }
// void add_env(t_env **head_en, char **split)
// {
//     int i = 1;
    
//     while (split[i])
//     {
        
//         if (split[i][0] == '\0' || !check_if_valid_args(split[i]))
//         {
//             i++;
//             continue;
//         }
//         process_env_argument(head_en, split[i]);
//         i++;
//     }
// }




void process_env_argument(t_env **head_en, char *arg)
{
    char *env_variable = get_env_variable(arg);
    char *env_value = get_env_value(arg);
   
    int concatenate = 0;
    if (env_variable[ft_strlen(env_variable) - 1] == '+')
    {
        if (env_variable[ft_strlen(env_variable) - 2] == '+')
        {
            printf("minishell: env: `%s': not a valid identifier\n", arg);
			g_shell.exit_status = EXIT_FAILURE;
            return;
        }
        concatenate = 1;
        env_variable[ft_strlen(env_variable) - 1] = '\0';
    }
    
    if (check_if_env_var_exist(*head_en, env_variable))
    {
        if (concatenate == 1)
        {
            concatenation_env(head_en, env_variable, env_value);
            return;
        }
        else
            remove_env_element(head_en, env_variable);
    }
    add_env_element(env_variable, env_value, head_en);
}

void add_env(t_env **head_en, char **split)
{
    int i = 1;
    
    while (split[i])
    {
        if (split[i][0] == '\0' || !check_if_valid_args(split[i]))
        {
            i++;
            continue;
        }
        process_env_argument(head_en, split[i]);
        i++;
    }
}
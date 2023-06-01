/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:06:45 by ahaloui           #+#    #+#             */
/*   Updated: 2023/05/30 03:03:11 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void cast_variables(int ac, char **av, char **environ)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)environ;
// }

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	if (!s1 || !s2 || !*s1 || !*s2)
		return (1);
	while(s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// int is_directory(char* command) 
// {
// 	if (access(command, F_OK) == 0) {
// 		DIR* dir = opendir(command);
// 		if (dir != NULL) {
// 			closedir(dir);
// 			return 1;
// 		} else {
// 			return 0;
// 		}
// 	} else {
// 		return 0;
// 	}
// }

char *get_value(t_export **head_ex, char *var)
{
    t_export *tmp;
    char *value;

    tmp = *head_ex;
	if (!tmp)
		return (NULL);
    while (tmp)
    {
        if (!ft_strcmp(tmp->export_var, var))
        {
            value = ft_strdup(tmp->export_value);
            return (value);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:40:58 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/04 21:39:46 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_is_numeric(char *split)
{
    int i;

    i = 0;
    while (split[i])
    {
        if (!ft_isdigit(split[i]))
            return (0);
        i++;
    }
    return (1);
}


int my_exit(t_cmd *commands)
{
    int i;
    int status_code;

    i = 1;
    status_code = 0;
    if (commands->cmds[i])
    {
        if (check_is_numeric(commands->cmds[i]))
        {
            status_code = ft_atoi(commands->cmds[i]);
            if (status_code > INT_MAX || status_code < INT_MIN)
            {
                printf("exit1111111\n");
                printf("exit\n");
                printf("minishell: exit: %s: numeric argument required\n", commands->cmds[i]);
                g_shell.exit_status = 255;
                return (1);   
            }
            if (commands->cmds[i + 1])
            {
                printf("exit\n");
                printf("minishell: exit: too many arguments\n");
                g_shell.exit_status = 1;
                return (1);
            }
        }
        else
        {
            printf("exit\n");
            printf("minishell: exit: %s: numeric argument required\n", commands->cmds[i]);
            g_shell.exit_status = 255;
            return (1);
        }
    }
    printf("exit\n");
    g_shell.exit_status = EXIT_SUCCESS;
    exit(EXIT_SUCCESS);
    return (0);
}
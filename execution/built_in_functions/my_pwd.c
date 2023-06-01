/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:40:01 by ahaloui           #+#    #+#             */
/*   Updated: 2023/05/28 02:39:13 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int my_pwd(t_info *info)
{
    char *path;    
    
    path = getcwd(NULL, 0);
    if (!path)
    {
        printf("minishell: pwd\n");
        path = get_export_value("PWD");
        printf("%s\n", get_value(&info->head_ex,"PWD"));
    }
    free(path);
    if (!(path = getcwd(NULL, 0)))
    {
        ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
        info->exit_status = 1;
        return (1);
    }
    else
    {
        ft_putstr_fd(path, 1);
        ft_putstr_fd("\n", 1);
    }
    free(path);    
    return (0);
}
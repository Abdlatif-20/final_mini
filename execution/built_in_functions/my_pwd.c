/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:40:01 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/05 17:26:43 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int my_pwd(t_info *info)
{
    char *path;    
    
    path = getcwd(NULL, 0);
    if (!path)
    {
        path = get_export_value("PWD");
        if (!path)
            ft_putstr_fd(getenv("PWD"), 1);
        ft_putstr_fd(get_value(&info->head_ex,"PWD"), 1);
        ft_putstr_fd("\n", 1);
    }
    else
    {
        ft_putstr_fd(path, 1);
        ft_putstr_fd("\n", 1);
    }
    free(path);    
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:40:58 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/03 21:03:32 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int status_code;

int my_exit(void)
{
    printf("exit\n");
    g_shell.exit_status = EXIT_SUCCESS;
    exit(0);
    return (0);
}
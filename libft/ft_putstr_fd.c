/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:44:14 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/15 23:20:51 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write (fd, s++, 1);
}

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_nbr(int nu, int fd)
{
    long int	n;

    n = nu;
    if (n < 0)
    {
        ft_putchar_fd('-', fd);
        n = n * (-1);
    }
    if (n < 10)
    {
        ft_putchar_fd(n + '0', fd);
    }
    else
    {
        ft_nbr(n / 10, fd);
        ft_nbr(n % 10 + '0', fd);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:47:52 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/07 18:38:25 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long long	ft_atoi(const char *str)
{
	long long		res;
	long long		sign;

	if (!str)
		return (0);
	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (sign * res);
}

long long	ft_atoi1(char *str, int *flag)
{
	long long		i;
	int					signe;
	long long	result;

	i = 0;
	result = 0;
	signe = 1;
	while (ft_whitespace(str[i]))
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		// if (str[i] < '0' || str[i] > '9')
		// {
		// 	*flag = 1;
		// 	return (-1);
		// }
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	if ((result < 0 && signe > 0) || ((result * signe) > 0 && signe < 0))
	{
		*flag = 1;
		return (-1);
	}
	return (result * signe);
}

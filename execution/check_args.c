/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:33:52 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/10 18:27:21 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_is_contain(char *split)
{
	int	i;

	i = 0;
	if (split[i] && split[i] == '\0')
		return (0);
	if (split[i] && !ft_isalpha(split[i]) && split[i] != '_')
		return (0);
	return (1);
}

int	check_if_valid_args(char *split)
{
	int	i;

	i = 0;
	if (split[i] && !check_is_contain(split))
		return (0);
	i = i + 1;
	while (split[i])
	{
		if (ft_isalnum(split[i]) || split[i] == '_' || split[i] == '=')
		{
			i++;
			continue ;
		}
		else if (split[i] == '+' && split[i + 1])
		{
			if (split[i + 1] == '\0' || split[i + 1] == '=')
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

char	*get_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i + 1));
}

int	check_export(char **split)
{
	int	i;
	int	valid;

	i = 1;
	valid = 1;
	while (split[i])
	{
		if (check_if_valid_args(get_arg(split[i])) == 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ft_putstr_fd(split[i], 2);
		}
		i++;
	}
	return (1);
}

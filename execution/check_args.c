/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:33:52 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/16 22:02:20 by ahaloui          ###   ########.fr       */
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

int	help_check_if_valid_args(char *split, int *i)
{
	if (split[*i] && (ft_isalnum(split[*i])
			|| split[*i] == '_' || split[*i] == '='))
	{
		*i = *i + 1;
		return (2);
	}
	else if (split[*i] && split[*i] == '+' && split[*i + 1])
	{
		if (split[*i + 1] == '\0' || split[*i + 1] == '=')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	check_if_valid_args(char *split)
{
	int	i;

	if (!split)
		return (0);
	i = 0;
	if (split[i] && !check_is_contain(split))
		return (0);
	i = i + 1;
	while (split[i])
	{
		if (help_check_if_valid_args(split, &i) == 2)
			continue ;
		else if (!help_check_if_valid_args(split, &i))
			return (0);
		i++;
	}
	return (1);
}

char	*get_arg(char *arg)
{
	int	i;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg && arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i + 1));
}

int	check_export(char **split, t_var *vars)
{
	int		i;
	char	*arg;

	i = 1;
	while (split[i])
	{
		arg = get_arg(split[i]);
		if (arg[0] == '\0' && !vars->is_empty_str)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(split[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_shell.exit_status = EXIT_FAILURE;
			free(arg);
			i++;
			continue ;
		}
		if (split[i] && check_if_valid_args(arg) == 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(split[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_shell.exit_status = EXIT_FAILURE;
		}
		free(arg);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:34:56 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/17 16:35:14 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_is_numeric(char *split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
	{
		if ((split[i] == '-' && i == 0) || (split[i] == '+' && i == 0
				&& ft_isdigit(split[i + 1])))
			i++;
		if (!ft_isdigit(split[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_white_spaces(char *split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
	{
		if (!ft_whitespace(split[i]))
			return (0);
		i++;
	}
	return (1);
}

void	special_case(t_cmd *commands, int i, int flag)
{
	(void)flag;
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(commands->cmds[i], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	if (!check_is_numeric(commands->cmds[i])
		&& (!check_is_numeric(commands->cmds[i + 1])))
		g_shell.exit_status = 255;
	else
		g_shell.exit_status = 1;
	exit(g_shell.exit_status);
}

void	help_case(t_cmd *commands, int i, int flag, long long *status_code)
{
	if (check_is_numeric(commands->cmds[i]) && !commands->cmds[i + 1])
	{
		*status_code = ft_atoi1(commands->cmds[i], &flag);
		if (*status_code >= 0 && !flag)
			case_positive(*status_code);
		else if (*status_code < 0 && !flag)
			case_negative(*status_code);
		else
			case1(commands, i);
	}
	else if (check_is_numeric(commands->cmds[i])
		&& check_is_numeric(commands->cmds[i + 1]))
		case2(commands);
	else if (check_is_numeric(commands->cmds[i])
		&& !check_is_numeric(commands->cmds[i + 1]))
		case2(commands);
	else if ((!check_is_numeric(commands->cmds[i])
			|| (*status_code == -1 && flag)))
		special_case(commands, i, flag);
}

int	my_exit(t_cmd *commands)
{
	int			i;
	int			flag;
	long long	status_code;
	char		*str;

	i = 1;
	status_code = 0;
	flag = 0;
	str = ft_strdup(commands->cmds[i]);
	if (check_white_spaces(str))
		case1(commands, i);
	free(str);
	str = skip_whitespace(str);
	if (str)
		help_case(commands, i, flag, &status_code);
	else
		default_case();
	return (free(str), 0);
}

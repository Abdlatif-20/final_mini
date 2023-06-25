/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.ma>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:19:27 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/25 02:47:12 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	help_unset(t_info *info, char *variable)
{
	remove_env_element(&info->head_en, variable);
	remove_export_element(&info->head_ex, variable);
}

void	print_unset_error(char *variable)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(variable, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	my_unset(t_cmd *cmd, t_info *info)
{
	int		i;
	int		flag;
	char	*variable;

	i = 1;
	variable = NULL;
	flag = 0;
	while (cmd->cmds[i])
	{
		variable = get_env_variable(cmd->cmds[i]);
		if (check_if_valid_args(cmd->cmds[i]) == 0 || variable[0] == '\0' )
		{
			print_unset_error(cmd->cmds[i]);
			free(variable);
			if (check_if_valid_args(cmd->cmds[i]) == 0)
				i++;
			continue ;
		}
		if (ft_strcmp(variable, "HOME") == 0)
			info->var->flag_home = 1;
		else
			help_unset(info, variable);
		free(variable);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:24:38 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/20 19:30:08 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	help_unset(t_info *info, char *variable)
{
	remove_env_element(&info->head_en, variable);
	remove_export_element(&info->head_ex, variable);
}

void	my_unset(t_cmd *cmd, t_info *info)
{
	int		i;
	int		flag;
	char	*variable;

	i = 0;
	variable = NULL;
	flag = 0;
	while (cmd->cmds[++i])
	{
		variable = get_env_variable(cmd->cmds[i]);
		if (check_if_valid_args(cmd->cmds[i]) == 0)
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd->cmds[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			free(variable);
			i++;
			continue ;
		}
		if (ft_strcmp(variable, "HOME") == 0)
			info->var->flag_home = 1;
		else
			help_unset(info, variable);
		free(variable);
	}
}

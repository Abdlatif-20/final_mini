/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:24:38 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/18 19:31:15 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	my_unset(t_cmd *cmd, t_info *info)
{
	int		i;
	char	*variable;

	i = 1;
	variable = NULL;
	while (cmd->cmds[i])
	{
		variable = get_env_variable(cmd->cmds[i]);
		if (check_if_valid_args(cmd->cmds[i]) == 0)
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd->cmds[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			i++;
			continue ;
		}
		remove_env_element(&info->head_en, variable);
		remove_export_element(&info->head_ex, variable);
		free(variable);
		i++;
	}
}

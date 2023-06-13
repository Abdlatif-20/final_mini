/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:24:38 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/13 21:15:32 by ahaloui          ###   ########.fr       */
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
		remove_env_element(&info->head_en, variable);
		remove_export_element(&info->head_ex, variable);
		free(variable);
		i++;
	}
}

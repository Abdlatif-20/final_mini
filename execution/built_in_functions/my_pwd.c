/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:40:01 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/09 22:10:27 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_value1(t_info *info)
{
	t_env	*temp;

	temp = info->head_en;
	while (temp)
	{
		if (!ft_strcmp(temp->env_var, "PWD"))
			return (ft_strdup(temp->env_value));
		temp = temp->next;
	}
	return (NULL);
}

int	my_pwd(t_info *info)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		path = get_value1(info);
		if (!path)
			ft_putstr_fd(getenv("PWD"), 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	free(path);
	return (0);
}

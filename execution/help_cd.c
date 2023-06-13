/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:44:31 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/13 16:24:07 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_value1(t_info *info, char *env_var, char *new_value)
{
	t_env	*temp;

	temp = info->head_en;
	while (temp)
	{
		if (!ft_strcmp(temp->env_var, env_var))
		{
			free(temp->env_value);
			temp->env_value = new_value;
		}
		temp = temp->next;
	}
}

char	*get_value2(t_info *info, char *env_var)
{
	t_env	*temp;

	temp = info->head_en;
	while (temp)
	{
		if (!ft_strcmp(temp->env_var, env_var))
			return (ft_strdup(temp->env_value));
		temp = temp->next;
	}
	return (NULL);
}

int	if_there_is_tilda(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

int	case_of_tilda_in_path(t_info *info, char *path_tmp1)
{
	if (!path_tmp1)
		return (0);
	if (!chdir(path_tmp1))
	{
		set_value1(info, "PWD", getcwd(NULL, 0));
		free(path_tmp1);
		return (1);
	}
	else
	{
		g_shell.exit_status = 1;
		printf("minishell$: cd: %s: No such file or directory\n", path_tmp1);
		return (free(path_tmp1), 0);
	}
}

int	case_of_remove_directory(t_cmd *commands, t_info *info, char **tmp, int i)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: cd: error retrieving current ", 2);
		ft_putstr_fd("directory: getcwd: cannot access ", 2);
		ft_putstr_fd("parent directories: No such file or directory\n", 2);
		*tmp = ft_strjoin(get_value2(info, "PWD"), "/");
		set_value1(info, "PWD", ft_strjoin(*tmp, commands->cmds[i]));
		return (0);
	}
	else
	{
		set_value1(info, "PWD", getcwd(NULL, 0));
		free(cwd);
		return (1);
	}
}

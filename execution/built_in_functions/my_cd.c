/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:51:03 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/12 16:43:57 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path_home(t_export **head_x)
{
	t_export	*temp;

	temp = *head_x;
	while (temp)
	{
		if (!ft_strcmp(temp->export_var, "HOME"))
			return (ft_strdup(temp->export_value));
		temp = temp->next;
	}
	return (NULL);
}

int	case_of_just_cd(t_info *info, char *path_home)
{
	set_value1(info, "OLDPWD", getcwd(NULL, 0));
	if (!chdir(path_home))
	{
		set_value1(info, "PWD", getcwd(NULL, 0));
		return (1);
	}
	else
	{
		g_shell.exit_status = 1,
		printf("minishell$: cd: %s: No such file or directory\n", path_home);
		return (0);
	}
}

int	case_of_cd_tilda(t_info *info, char *path_home)
{
	set_value1(info, "OLDPWD", getcwd(NULL, 0));
	if (!chdir(path_home))
	{
		set_value1(info, "PWD", getcwd(NULL, 0));
		return (1);
	}
	else
	{
		g_shell.exit_status = 1,
		printf("minishell$: cd: %s: No such file or directory\n", path_home);
		return (0);
	}
}

int	help_cd(t_info *info, char *path_home, t_cmd *commands, int i)
{
	if (!ft_strcmp(commands->main_cmd, "cd") && !commands->cmds[i])
	{
		if (!path_home)
		{
			printf("minishell$: cd: HOME not set\n");
			// reserve_list(info);
			return ( 0);
		}
		return (case_of_just_cd(info, path_home));
	}
	else if (!ft_strcmp(commands->main_cmd, "cd")
		&& !ft_strcmp(commands->cmds[i], "~"))
		return (case_of_cd_tilda(info, path_home));
	return (1);
}

int	my_cd(t_cmd *commands, t_info *info)
{
	int		i;
	char	*path_home;
	char	*tmp;

	i = 1;
	tmp = NULL;
	path_home = get_path_home(&info->head_ex);
	if (!help_cd(info, path_home, commands, i))
	{
		free(path_home);
		return (0);
	}
	else if (!ft_strcmp(commands->main_cmd, "cd") && commands->cmds[i])
	{
		set_value1(info, "OLDPWD", getcwd(NULL, 0));
		if (if_there_is_tilda(commands->cmds[i]))
		{
			case_of_tilda_in_path(info, ft_strjoin(path_home,
					ft_substr(commands->cmds[i], 1,
						ft_strlen(commands->cmds[i]))));		
		}
		else if (!chdir(commands->cmds[i]))
			case_of_remove_directory(commands, info, &tmp, i);
		else
			return (g_shell.exit_status = 1,
				printf("minishell$: cd: %s: No such file or directory\n",
					commands->cmds[i]), 0);
	}
	free(path_home);
	return (1);
}

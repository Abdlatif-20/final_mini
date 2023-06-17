/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:51:03 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/17 18:27:25 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	case_of_just_cd(t_info *info, char *path_home)
{
	set_value1(info, "OLDPWD", getcwd(NULL, 0));
	if (!chdir(path_home))
	{
		set_value1(info, "PWD", getcwd(NULL, 0));
		free(path_home);
		return (1);
	}
	else
	{
		g_shell.exit_status = 1;
		printf("minishell$: cd: %s: No such file or directory\n", path_home);
		return (free(path_home), 0);
	}
}

int	case_of_cd_tilda(t_info *info, char *path_home)
{
	set_value1(info, "OLDPWD", getcwd(NULL, 0));
	if (!chdir(path_home))
	{
		set_value1(info, "PWD", getcwd(NULL, 0));
		free(path_home);
		return (1);
	}
	else
	{
		g_shell.exit_status = 1;
		printf("minishell$: cd: %s: No such file or directory\n", path_home);
		return (free(path_home), 0);
	}
}

int	help_case_1(char *path_home, t_info *info)
{
	if (!path_home)
	{
		printf("minishell$: cd: HOME not set\n");
		return (free(path_home), 0);
	}
	if (case_of_just_cd(info, path_home))
		return (1);
	else
		return (0);
}

int	help_case_2(t_cmd *commands, t_info *info, char *path_home)
{
	char	*tmp2;
	char	*tmp;

	tmp = NULL;
	tmp2 = NULL;
	if (if_there_is_tilda(commands->cmds[1]))
	{
		tmp2 = ft_substr(commands->cmds[1], 1, ft_strlen(commands->cmds[1]));
		if (case_of_tilda_in_path(info, ft_strjoin(path_home, tmp2)))
			return (free(tmp2), 1);
		else
			return (free(tmp2), 0);
	}
	else if (!chdir(commands->cmds[1]))
	{
		if (!case_of_remove_directory(commands, info, &tmp, 1))
			return (free(path_home), 0);
		return (free(tmp), free(path_home), 1);
	}
	else
	{
		printf("minishell$: cd: %s: No such file or directory\n",
			commands->cmds[1]);
		return (free(path_home), g_shell.exit_status = 1, 0);
	}	
}

int	my_cd(t_cmd *commands, t_info *info)
{
	char	*path_home;

	path_home = get_path_home(&info->head_ex);
	if (!ft_strcmp(commands->main_cmd, "cd") && !commands->cmds[1])
		return (help_case_1(path_home, info));
	else if (!ft_strcmp(commands->main_cmd, "cd")
		&& !ft_strcmp(commands->cmds[1], "~"))
	{
		if (case_of_cd_tilda(info, path_home))
			return (1);
		else
			return (0);
	}
	else if (!ft_strcmp(commands->main_cmd, "cd") && commands->cmds[1])
	{
		set_value1(info, "OLDPWD", getcwd(NULL, 0));
		return (help_case_2(commands, info, path_home));
	}
	return (free(path_home), 1);
}

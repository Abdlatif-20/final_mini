/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:51:03 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/07 20:21:25 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

char *get_path_home(t_export **head_x)
{
	t_export *temp;

	temp = *head_x;
	while (temp)
	{
		if (!ft_strcmp(temp->export_var, "HOME"))
			return (ft_strdup(temp->export_value));
		temp = temp->next;
	}
	return (NULL);
}



void set_value1(t_info *info, char *env_var, char *new_value)
{
	t_env *temp;
	
	temp = info->head_en;
	while (temp)
	{
		if (!ft_strcmp(temp->env_var, env_var))
			temp->env_value = new_value;
		temp = temp->next;
	}
}

char *get_value2(t_info *info, char *env_var)
{
	t_env *temp;

	temp = info->head_en;
	while (temp)
	{
		if (!ft_strcmp(temp->env_var, env_var))
			return (ft_strdup(temp->env_value));
		temp = temp->next;
	}
	return (NULL);
}

int if_there_is_tilda(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

int my_cd(t_cmd *commands, t_info *info)
{
	int i;
	char *path_home;
	char *path_tmp;
	char *path_tmp1;
	
	i = 1;
	path_home = get_path_home(&info->head_ex);
	if (!path_home)
	{
		printf("minishell$: cd: HOME not set\n");
		return (0);
	}
	if (!ft_strcmp(commands->main_cmd, "cd") && !commands->cmds[i])
	{
		set_value1(info, "OLDPWD", getcwd(NULL, 0));
		if (!chdir(path_home))
		{
			set_value1(info, "PWD", getcwd(NULL, 0));
			return (1);
		}
	}
	else if (!ft_strcmp(commands->main_cmd, "cd") && !ft_strcmp(commands->cmds[i], "~"))
	{
		set_value1(info, "OLDPWD", getcwd(NULL, 0));
		if (!chdir(path_home))
		{
			set_value1(info, "PWD", getcwd(NULL, 0));
			return (1);
		}
	}
	else if (!ft_strcmp(commands->main_cmd, "cd") && commands->cmds[i])
	{
		
		set_value1(info, "OLDPWD", getcwd(NULL, 0));
		if (if_there_is_tilda(commands->cmds[i]))
		{
			path_tmp = ft_substr(commands->cmds[i], 1, ft_strlen(commands->cmds[i]));
			path_tmp1 = ft_strjoin(path_home, path_tmp);
			if (!path_tmp || !path_tmp1)
				return (0);
			if (!chdir(path_tmp1))
			{
				set_value1(info, "PWD", getcwd(NULL, 0));
				return (1);
			}
			else
			{
				printf("minishell$: cd: %s: No such file or directory\n", path_tmp1);
				return (0);
			}
		}
		else if (!chdir(commands->cmds[i]))
		{
			if (!getcwd(NULL, 0))
			{
				puts("error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");
				char *tmp = ft_strjoin(get_value2(info, "PWD"),"/");
				set_value1(info, "PWD",ft_strjoin(tmp, commands->cmds[i]));
			}
			else
				set_value1(info, "PWD", getcwd(NULL, 0));
			return (1);	
		}
		else
		{
			printf("minishell$: cd: %s: No such file or directory\n", commands->cmds[i]);	
			return (0);
		}
	}
	return (1);
}

// char *current_dir = getcwd(NULL, 0);
//     	if (current_dir == NULL)
//     	{
//         	char *current_cmd = ft_strjoin("cd ", commands->cmds[i]);
//         	printf("bash-3.2$ %s: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", current_cmd);
//         	free(current_cmd);
//         	return 0;
//     	}

// void set_current_directory(t_info *infos, char *path)
// {
//     char *tmp;
//     char *removed_pwd;
//     char *slash_path;
//     char *old_pwd;

//     tmp = getcwd(NULL, 0);
//     if (!tmp)
//     {
//         slash_path = ft_strjoin("/", path);
//         old_pwd = get_value2(infos, "OLDPWD");
//         removed_pwd = ft_strjoin(old_pwd, slash_path);
//         set_value1(infos, "PWD", getcwd(NULL, 0));
//         free(removed_pwd);
//         if (!old_pwd)
//             free(slash_path);
//     }
//     else
//         set_value1(infos, "PWD", getcwd(NULL, 0));
//     free(tmp);
// }

// int my_cd(t_cmd *commands, t_info *info)
// {
//     int i;
//     char *path_home;
//     char *path_tmp;
//     char *path_tmp1;

//     i = 1;
//     path_home = get_path_home(&info->head_ex);
//     if (!path_home)
//     {
//         printf("minishell$: cd: HOME not set\n");
//         return (0);
//     }
//     if (!ft_strcmp(commands->main_cmd, "cd") && !commands->cmds[i])
//     {
//         set_value1(info, "OLDPWD", getcwd(NULL, 0));
//         if (!chdir(path_home))
//         {
//             set_value1(info, "PWD", getcwd(NULL, 0));
//             set_current_directory(info, path_home);
//             return (1);
//         }
//     }
//     else if (!ft_strcmp(commands->main_cmd, "cd") && !ft_strcmp(commands->cmds[i], "~"))
//     {
//         set_value1(info, "OLDPWD", getcwd(NULL, 0));
//         if (!chdir(path_home))
//         {
//             set_value1(info, "PWD", getcwd(NULL, 0));
//             set_current_directory(info, path_home);
//             return (1);
//         }
//     }
//     else if (!ft_strcmp(commands->main_cmd, "cd") && commands->cmds[i])
//     {
//         set_value1(info, "OLDPWD", getcwd(NULL, 0));
//         if (if_there_is_tilda(commands->cmds[i]))
//         {
//             path_tmp = ft_substr(commands->cmds[i], 1, ft_strlen(commands->cmds[i]));
//             path_tmp1 = ft_strjoin(path_home, path_tmp);
//             if (!path_tmp || !path_tmp1)
//                 return (0);
//             if (!chdir(path_tmp1))
//             {
//                 set_value1(info, "PWD", getcwd(NULL, 0));
//                 set_current_directory(info, path_tmp1);
//                 return (1);
//             }
//             else
//             {
//                 printf("minishell$: cd: %s: No such file or directory\n", path_tmp1);
//                 return (0);
//             }
//         }
//         else if (!chdir(commands->cmds[i]))
//         {
//             set_value1(info, "PWD", getcwd(NULL, 0));
//             set_current_directory(info, commands->cmds[i]);
//             return (1);
//         }
//         else
//         {
//             printf("minishell$: cd: %s: No such file or directory\n", commands->cmds[i]);
//             return (0);
//         }
//     }
//     return (1);
// }
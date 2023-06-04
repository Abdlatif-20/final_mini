/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:04:31 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/04 23:48:38 by ahaloui          ###   ########.fr       */
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
			return (temp->export_value);
		temp = temp->next;
	}
	return (NULL);
}

char *get_old_path(t_export **head_x)
{
	t_export *temp;

	temp = *head_x;
	while (temp)
	{
		if (!ft_strcmp(temp->export_var, "OLDPWD"))
			return (temp->export_value);
		temp = temp->next;
	}
	return (NULL);
}

char *get_path(t_export **head_x)
{
	t_export *temp;

	temp = *head_x;
	while (temp)
	{
		if (!ft_strcmp(temp->export_var, "PWD"))
			return (temp->export_value);
		temp = temp->next;
	}
	return (NULL);
}
void set_value(t_export **head_ex, char *export_var, char *new_value)
{
	t_export *temp;
	
	temp = *head_ex;
	while (temp)
	{
		if (!ft_strcmp(temp->export_var, export_var))
			temp->export_value = new_value;
		temp = temp->next;
	}
}

void init_pwd(t_export **head_ex)
{
	t_export *temp;

	temp = *head_ex;
	while (temp)
	{
		if (!ft_strcmp(temp->export_var, "PWD"))
			temp->export_value = NULL;
		temp = temp->next;
	}
}

int get_pos(char *str, char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int my_cd(t_cmd *commands, t_info *info)
{
	int i = 1;
	static int flag = 1;
	char *path = commands->cmds[i];
	char *old_path = get_path(&info->head_ex);
	
	
	if (getcwd(NULL, 0) == NULL)
	{
		printf("minishell$: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		path = get_path_home(&info->head_ex);
		if(!path)
			return (0);
		path = ft_strjoin(old_path, "/");
		path = ft_strjoin(path, commands->cmds[i]);
		set_value(&info->head_ex, "PWD", path);
		return (1);
	}
	if (commands->main_cmd && !ft_strcmp(commands->main_cmd, "cd") 
		&& !commands->cmds[1])
	{
		path = get_path_home(&info->head_ex);
		if(!path)
		{
			printf("minishell$: cd: HOME not set\n");
			return (0);
		}
		if (chdir(path))
			return(1);
			flag = 0;
	}
	if (commands->cmds[i] && !ft_strcmp(commands->cmds[i], "~"))
	{
		path = get_path_home(&info->head_ex);
		if(!path)
			return (0);
		if (chdir(path))
			return(1);
	}
	else if (commands->cmds[i] && !ft_strcmp(commands->cmds[i], "-"))
	{
		if (flag)
			printf("minishell$: cd: OLDPWD not set\n");
		else
		{
			old_path = get_old_path(&info->head_ex);
			if (!old_path)
				return (0);
			if (chdir(old_path))
				return (1);
			printf("%s\n", old_path);
		flag = 0;
		}
	}
	else if (commands->cmds[i])
	{
		char *str;
		char *temp;

		str = ft_substr(path, 0, get_pos(path, '/'));
		temp = ft_substr(path, get_pos(path, '/') + 1, ft_strlen(path) - 1);
		if (!ft_strcmp(str, "~"))
		{
			path = get_path_home(&info->head_ex);
			if(!str)
				return (0);
			if (chdir(path) || chdir(temp))
			{
				printf("minishell$: cd: %s/%s: No such file or directory\n", path, temp);	
				return (1);
			}
			flag = 0;
		}
		else if (commands->cmds[i])
		{ 
			if (!path)
				return (0); 
			else if (chdir(path))
			{
				printf("minishell$: cd: %s: No such file or directory\n", path);	
				return (1);
			}
			set_value(&info->head_ex, "PWD", path);
			flag = 0;
		}
		free(str);
		free(temp);
	}
	// set_value(&info->head_ex, "OLDPWD", get_path(&info->head_ex));
	set_value(&info->head_ex, "PWD", getcwd(NULL, 0));
	return (0);
}

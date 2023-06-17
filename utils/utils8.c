/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:16:25 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/15 15:42:34 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_export_ignored(t_info *info)
{
	char	*tmp;
	char	*name;

	tmp = getcwd(NULL, 0);
	name = ft_strdup("/./minishell");
	ft_lst_add_back_export(&info->head_ex,
		ft_lst_new_export(ft_strdup("PWD"), ft_strdup(tmp), 1));
	ft_lst_add_back_export(&info->head_ex,
		ft_lst_new_export(ft_strdup("SHLVL"), ft_strdup("1"), 1));
	ft_lst_add_back_export(&info->head_ex,
		ft_lst_new_export(ft_strdup("_"), ft_strjoin(ft_strdup(tmp), name), 1));
	ft_lst_add_back_export(&info->head_ex,
		ft_lst_new_export(ft_strdup("OLDPWD"), ft_strdup(""), 1));
	ft_lst_add_back_export(&info->head_ex,
		ft_lst_new_export(ft_strdup("PATH"),
			ft_strdup("/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"), 1));
	free(tmp);
	free(name);
}

void	add_env_ignored(t_info *info)
{
	char	*tmp;
	char	*name;

	tmp = getcwd(NULL, 0);
	name = ft_strdup("/./minishell");
	ft_lst_add_back_env(&info->head_en,
		ft_lst_new_env(ft_strdup("PWD"), ft_strdup(tmp), 1));
	ft_lst_add_back_env(&info->head_en,
		ft_lst_new_env(ft_strdup("SHLVL"), ft_strdup("1"), 1));
	ft_lst_add_back_env(&info->head_en,
		ft_lst_new_env(ft_strdup("_"), ft_strjoin(ft_strdup(tmp), name), 1));
	ft_lst_add_back_env(&info->head_en,
		ft_lst_new_env(ft_strdup("OLDPWD"), ft_strdup(""), 1));
	ft_lst_add_back_env(&info->head_en,
		ft_lst_new_env(ft_strdup("PATH"),
			ft_strdup("/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"), 1));
	free(tmp);
	free(name);
}

void	free_split_paths(char **split_paths)
{
	int	i;

	i = 0;
	while (split_paths[i])
	{
		if (split_paths[i])
			free(split_paths[i]);
		i++;
	}
	free(split_paths);
	split_paths = NULL;
}

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

void	help_main(t_info *info, char **env)
{
	if (env == NULL || *env == NULL)
	{
		add_export_ignored(info);
		add_env_ignored(info);
	}
	fill_export_list(env, &(*info).head_ex);
	fill_env_list(env, &(*info).head_en);
}

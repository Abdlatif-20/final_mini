/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:16:25 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/14 01:32:29 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_export_ignored(t_info *info)
{
	ft_lst_add_back_export(&info->head_ex,
		ft_lst_new_export(ft_strdup("PWD"), ft_strdup(getcwd(NULL, 0))));
	ft_lst_add_back_export(&info->head_ex,
		ft_lst_new_export(ft_strdup("SHLVL"), ft_strdup("1")));
	ft_lst_add_back_export(&info->head_ex,
		ft_lst_new_export(ft_strdup("_"),
			ft_strjoin(ft_strdup(getcwd(NULL, 0)), ft_strdup("/./minishell"))));
	ft_lst_add_back_export(&info->head_ex,
		ft_lst_new_export(ft_strdup("OLDPWD"), ft_strdup("")));
	ft_lst_add_back_export(&info->head_ex,
		ft_lst_new_export(ft_strdup("PATH"),
			ft_strdup("/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin")));
}

void	add_env_ignored(t_info *info)
{
	ft_lst_add_back_env(&info->head_en,
		ft_lst_new_env(ft_strdup("PWD"), ft_strdup(getcwd(NULL, 0))));
	ft_lst_add_back_env(&info->head_en,
		ft_lst_new_env(ft_strdup("SHLVL"), ft_strdup("1")));
	ft_lst_add_back_env(&info->head_en,
		ft_lst_new_env(ft_strdup("_"),
			ft_strjoin(ft_strdup(getcwd(NULL, 0)), ft_strdup("/./minishell"))));
	ft_lst_add_back_env(&info->head_en,
		ft_lst_new_env(ft_strdup("OLDPWD"), ft_strdup("")));
	ft_lst_add_back_env(&info->head_en,
		ft_lst_new_env(ft_strdup("PATH"),
			ft_strdup("/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin")));
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

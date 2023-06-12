/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:50:59 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/11 22:57:24 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_variable_name(char *name)
{
	if (ft_strchr(name, '$'))
		return (ft_strdup(strchr(name, '$') + 1));
	else
		return (NULL);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!*array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	init_variable1(t_env **env_tmp, t_env *env, t_var *var)
{
	*env_tmp = env;
	var->i = 0;
	var->string = NULL;
	var->str = NULL;
	var->temp = NULL;
	var->env = env;
}

void	ft_expand(t_list **list, t_env *env)
{
	t_var		var;

	var.tmp = *list;
	init_variable1(&var.tmp_env, env, &var);
	while (var.tmp)
	{
		var.token = var.tmp->data;
		if (var.tmp && var.token->key == VAR && var.token->is_herdoc == 0)
		{
			if (handel_var(&var.token, &var, var.env) == 2)
				continue ;
		}
		else if (var.tmp && var.token->key == DQUATES && !var.token->is_herdoc)
			handl_expand_dquotes(&var);
		var.tmp = var.tmp->next;
	}
}

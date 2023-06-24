/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.ma>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:34:30 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/24 03:24:32 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_variable(t_var *var, char *name)
{
	var->i = 0;
	var->j = 0;
	var->end = ft_strlen(name) - 1;
	var->str = (char *)malloc(ft_strlen(name) + 1);
}

char	*get_variable_name(char *name)
{
	t_var	var;

	init_variable(&var, name);
	if (!var.str)
		return (NULL);
	if (name[var.i] == '$')
		var.i++;
	while (name[var.i] && name[var.i] != '$'
		&& name[var.i] != ' ' && var.i <= var.end)
	{
		var.str[var.j++] = name[var.i++];
	}
		var.str[var.j] = '\0';
	return (var.str);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (free(array));
	while (array[i])
		free(array[i++]);
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

int	ft_expand(t_list **list, t_env *env, t_var *v)
{
	t_var		var;
	int			flag;

	flag = 0;
	var.tmp = *list;
	init_variable1(&var.tmp_env, env, &var);
	while (var.tmp)
	{
		var.token = var.tmp->data;
		if ((var.tmp && var.token->key == VAR && !var.token->is_herdoc)
			|| (v->flag_expand && var.token->key == RED_FILE))
		{
			if (handel_var(&var.token, &var, var.env, &flag) == 2)
				continue ;
		}
		else if ((var.tmp && var.token->key == DQUATES && !var.token->is_herdoc)
			|| (v->flag_expand && var.token->key == RED_FILE))
			handl_expand_dquotes(&var);
		var.tmp = var.tmp->next;
	}
	return (flag);
}

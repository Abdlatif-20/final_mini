/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:45:25 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/08 05:16:54 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_variable(t_var *var, char *name)
{
	var->i = 0;
	var->j = 0;
	var->flag = 0;
	var->end = ft_strlen(name) - 1;
	var->str = (char *)malloc(ft_strlen(name) + 1);
}

char	*get_variable_name(char *name)
{
	t_var	var;

	init_variable(&var, name);
	if (!var.str)
		return (NULL);
	while (name[var.i] && (name[var.i] == '\''
			|| name[var.i] == '\"' || name[var.i] == '|'))
		var.i++;
	while (name[var.end] && (name[var.end] == '\''
			|| name[var.end] == '\"' || name[var.end] == '|'))
		var.end--;
	if (name[var.i] == '$')
		var.i++;
	while (name[var.i] && name[var.i] != '$'
		&& name[var.i] != ' ' && var.i <= var.end)
	{
		var.str[var.j++] = name[var.i++];
		var.flag = 1;
	}
	if (var.flag)
		var.str[var.j] = '\0';
	return (var.str);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	ft_expand(t_list **list, t_env *env)
{
	t_list		*tmp;
	t_env		*tmp_env;
	t_token		*token;
	t_var		var;

	tmp = *list;
	tmp_env = env;
	var.i = 0;
	while (tmp)
	{
		token = tmp->data;
		if (tmp && token->key == VAR && token->is_herdoc == 0)
		{
			if (handel_var(&list, &token, &var, env) == 2)
				continue ;
			env = var.tmp_env;
		}
		else if (tmp && token->key == DQUATES && token->is_herdoc == 0)
		{
			if (expand_dquotes(&tmp, &token, &var, env) == 2)
				continue ;
		}
		tmp = tmp->next;
	}
}

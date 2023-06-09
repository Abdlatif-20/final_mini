/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:49:49 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/09 23:42:35 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handel_var(t_list ***list, t_token **token, t_var *var, t_env *env)
{
	if ((*token)->value[0] == '$'
		&& ft_isdigit((*token)->value[1]))
	{
		var->len = 0;
		if ((*token)->value[var->i] != '$')
		{
			while ((*token)->value[var->i + var->len]
				&& (*token)->value[var->i + var->len] != '$')
				var->len++;
			var->str = ft_substr((*token)->value, var->i, var->len);
			(*token)->value = ft_strdup(var->str);
		}
		var->i++;
		if (ft_isdigit((*token)->value[var->i]))
		{
			var->i++;
			return (2);
		}
	}
	else
		ft_expender_help(&list, &token, env, &var);
	return (0);
}

int	ft_expender_help(t_list ****list, t_token ***token, t_env *env, t_var **var)
{
	(void)list;
	if (ft_strcmp((**token)->value, "$?") == 0)
		return ((**token)->value = ft_itoa(g_shell.exit_status), 0);
	while (env)
	{
		(*var)->temp = get_variable_name((**token)->value);
		if (env && !ft_strcmp(env->env_var, (*var)->temp))
		{
			(**token)->value = ft_strdup(env->env_value);
			// temp = ft_split((**token)->value, ' ');
			// 	(**token)->value = ft_strdup(temp[0]);
			// fill_token((**list), W_SPACE, ft_strdup(" "), 0);
			// fill_token((**list), FLAG, ft_strdup(temp[1]), 0);
			// free_array(temp);
			env = (*var)->tmp_env;
			return (0);
		}
		env = env->next;
	}
	if (ft_strlen((**token)->value) == 1)
		(**token)->value = ft_strdup("$");
	else if (!env)
		(**token)->value = ft_strdup("");
	return (0);
}

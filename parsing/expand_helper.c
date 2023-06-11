/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:27:02 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/11 15:18:26 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handel_var(t_token **token, t_var *var, t_env *env)
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
		ft_expender_help(&token, env, &var);
	return (0);
}

int	ft_expender_help(t_token ***token, t_env *env, t_var **var)
{
	static char	*str;

	while (env)
	{
		(*var)->temp = get_variable_name((**token)->value);
		if ((*var)->temp && (*var)->temp[0] == '?')
		{
			str = ft_itoa(g_shell.exit_status);
			(**token)->value = ft_strdup(str);
			(**token)->value = ft_strjoin((**token)->value, &(*var)->temp[1]);
			return (free((*var)->temp), 0);
		}
		if (env && !ft_strcmp(env->env_var, (*var)->temp))
		{
			(**token)->value = ft_strdup(env->env_value);
			env = (*var)->tmp_env;
			return (free((*var)->temp), 0);
		}
		env = env->next;
	}
	if (ft_strlen((**token)->value) == 1)
		(**token)->value = ft_strdup("$");
	else if (!env)
		(**token)->value = ft_strdup("");
	return (0);
}

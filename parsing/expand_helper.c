/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:27:02 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/21 17:26:24 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handel_var(t_token **token, t_var *var, t_env *env, int *flag)
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
			free((*token)->value);
			(*token)->value = ft_strdup(var->str);
			free(var->str);
		}
		var->i++;
		if (ft_isdigit((*token)->value[var->i]))
		{
			var->i++;
			return (2);
		}
	}
	else
		ft_expender_help(token, env, var, flag);
	return (0);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

int	get_var(t_token **token, t_env *env, t_var *var)
{
	char	*str;

	str = NULL;
	if (var->temp && var->temp[0] == '?')
	{
		str = ft_itoa(g_shell.exit_status);
		free((*token)->value);
		(*token)->value = ft_strdup(str);
		ft_free(str);
		(*token)->value = ft_strjoin((*token)->value, &var->temp[1]);
		ft_free(var->temp);
		return (0);
	}
	if (env && !ft_strcmp(env->env_var, var->temp))
	{
		free((*token)->value);
		(*token)->value = ft_strdup(env->env_value);
		env = var->tmp_env;
		ft_free(var->temp);
		return (0);
	}
	return (1);
}

int	ft_expender_help(t_token **token, t_env *env, t_var *var, int *flag)
{
	while (env)
	{
		var->temp = get_variable_name((*token)->value);
		if (!get_var(token, env, var))
			return (0);
		env = env->next;
		ft_free(var->temp);
	}
	if (ft_strlen((*token)->value) == 1)
	{
		ft_free((*token)->value);
		(*token)->value = ft_strdup("$");
	}
	else if (!env)
	{
		free((*token)->value);
		(*token)->value = ft_strdup("");
		*flag = 1;
	}
	return (*flag);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 03:35:09 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/08 04:52:13 by aben-nei         ###   ########.fr       */
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

int	ft_expender_help2(t_token **token, t_var *var)
{
	if ((*token)->value[var->i + 1] == '\0'
		|| !ft_isalnum((*token)->value[var->i + 1]))
	{
		var->len = 1;
		while ((*token)->value[var->i + var->len]
			&& !ft_isalnum((*token)->value[var->i + var->len]))
			var->len++;
		if (var->len > 0)
			var->string = ft_strjoin(var->string,
					ft_substr((*token)->value,
						var->i, var->len));
		var->i += var->len;
	}
	else if ((*token)->value[var->i] == '$')
	{
		var->i++;
		if (ft_isdigit((*token)->value[var->i]))
		{
			var->i++;
			return (2);
		}
	}
	return (0);
}

int	ft_expender_help(t_list ****list, t_token ***token, t_env *env, t_var **var)
{
	char	**temp;

	if (ft_strcmp((**token)->value, "$?") == 0)
		return ((**token)->value = ft_itoa(g_shell.exit_status), 0);
	while (env)
	{
		(*var)->temp = get_variable_name((**token)->value);
		if ((**list) && !ft_strcmp(env->env_var, (*var)->temp))
		{
			(**token)->value = ft_strdup(env->env_value);
			temp = ft_split((**token)->value, ' ');
				(**token)->value = ft_strdup(temp[0]);
			fill_token((**list), W_SPACE, ft_strdup(" "), 0);
			fill_token((**list), FLAG, ft_strdup(temp[1]), 0);
			free_array(temp);
			break ;
		}
		env = env->next;
	}
	if (ft_strlen((**token)->value) == 1)
		(**token)->value = ft_strdup("$");
	else if (!env)
		(**token)->value = ft_strdup("");
	return (0);
}

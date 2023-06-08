/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 04:30:34 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/08 05:15:20 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_expender_help1(t_token ***token, t_var **var)
{
	(*var)->len = 0;
	while ((**token)->value[(*var)->i + (*var)->len]
		&& (**token)->value[(*var)->i + (*var)->len] != '$')
		(*var)->len++;
	if ((*var)->len > 0)
	{
		(*var)->temp = ft_substr((**token)->value, (*var)->i, (*var)->len);
		(*var)->string = ft_strjoin((*var)->string, (*var)->temp);
		free((*var)->temp);
	}
	(*var)->i += (*var)->len;
}

void	expand_dquotes_help1(t_token ***token, t_var **var)
{
	if ((**token)->value[(*var)->i + 1]
		&& !ft_isalpha((**token)->value[(*var)->i + 1])
		&& (**token)->value[(*var)->i + 1] != '_')
	{
		(*var)->len = 0;
		while ((**token)->value[(*var)->i + (*var)->len]
			&& !ft_isalpha((**token)->value[(*var)->i + (*var)->len])
			&& (**token)->value[(*var)->i + (*var)->len] != '_')
				(*var)->len++;
		if ((*var)->len > 0)
			(*var)->string = ft_strjoin((*var)->string,
					ft_substr((**token)->value, (*var)->i, (*var)->len));
		(*var)->i += (*var)->len;
	}
	(*var)->len = 0;
	while ((**token)->value[(*var)->i + (*var)->len]
		&& (**token)->value[(*var)->i + (*var)->len] != '$'
		&& (**token)->value[(*var)->i + (*var)->len] != ' '
		&& (ft_isalpha((**token)->value[(*var)->i + (*var)->len])
			|| (**token)->value[(*var)->i + (*var)->len] == '_'))
			(*var)->len++;
	(*var)->str = ft_substr((**token)->value, (*var)->i, (*var)->len);
	(*var)->i += (*var)->len;
}

int	expand_dquotes_help(t_token ***token, t_var **var)
{
	if ((**token)->value[(*var)->i + 1] == '\0'
		|| !ft_isalnum((**token)->value[(*var)->i + 1]))
	{
		(*var)->len = 1;
		while ((**token)->value[(*var)->i + (*var)->len]
			&& !ft_isalnum((**token)->value[(*var)->i + (*var)->len]))
			(*var)->len++;
		if ((*var)->len > 0)
			(*var)->string = ft_strjoin((*var)->string,
					ft_substr((**token)->value,
						(*var)->i, (*var)->len));
		(*var)->i += (*var)->len;
	}
	else if ((**token)->value[(*var)->i] == '$')
	{
		(*var)->i++;
		if (ft_isdigit((**token)->value[(*var)->i]))
		{
			(*var)->i++;
			return (2);
		}
	}
	return (0);
}

void	get_value_of_var(t_var **var, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->env_var, (*var)->str))
		{
			if ((*var)->len > 0)
			{
				(*var)->string = ft_strjoin((*var)->string,
						env->env_value);
				free((*var)->str);
			}
			break ;
		}
		env = env->next;
	}
}

int	expand_dquotes(t_list **tmp, t_token **token, t_var *var, t_env *env)
{
	var->string = NULL;
	while ((*token)->value[var->i])
	{
		ft_expender_help1(&token, &var);
		if ((*token)->value[var->i] == '$')
		{
			if (expand_dquotes_help(&token, &var) == 2)
				return (2);
			expand_dquotes_help1(&token, &var);
			get_value_of_var(&var, env);
			env = var->tmp_env;
		}
	}
	if (var->string)
		((t_token *)(*tmp)->data)->value = var->string;
	return (0);
}

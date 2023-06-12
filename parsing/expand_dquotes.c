/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 12:16:15 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/11 20:24:11 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	hold_string(t_var **var, t_token *token)
{
	char *tmp;

	(*var)->len = 0;
	while (token->value[(*var)->i + (*var)->len]
		&& token->value[(*var)->i + (*var)->len] != '$')
		(*var)->len++;
	if ((*var)->len > 0)
	{
		tmp = ft_substr(token->value, (*var)->i, (*var)->len);
		(*var)->string = ft_strjoin((*var)->string, tmp);
		ft_free(tmp);
	}
	(*var)->i += (*var)->len;
}

int	help_expand(t_var **var, t_token *token)
{
	if (token->value[(*var)->i + 1] == '\0'
		|| !ft_isalnum(token->value[(*var)->i + 1]))
	{
		(*var)->len = 1;
		if (token->value[(*var)->i + (*var)->len] == '?')
		{
			(*var)->temp = ft_itoa(g_shell.exit_status);
			(*var)->string = ft_strjoin((*var)->string, (*var)->temp);
			free((*var)->temp);
			(*var)->i += 2;
			return (2);
		}
		while (token->value[(*var)->i + (*var)->len]
			&& !ft_isalnum(token->value[(*var)->i + (*var)->len]))
			(*var)->len++;
		if ((*var)->len > 0)
			(*var)->string = ft_strjoin((*var)->string,
					ft_substr(token->value,
						(*var)->i, (*var)->len));
		(*var)->i += (*var)->len;
	}
	return (0);
}

int	help_expand1(t_var **var, t_token *token)
{
	if (token->value[(*var)->i] == '$')
	{
		(*var)->i++;
		if (ft_isdigit(token->value[(*var)->i]))
		{
			(*var)->i++;
			return (2);
		}
	}
	else if (token->value[(*var)->i + 1]
		&& !ft_isalpha(token->value[(*var)->i + 1])
		&& token->value[(*var)->i + 1] != '_')
	{
		(*var)->len = 0;
		while (token->value[(*var)->i + (*var)->len]
			&& !ft_isalpha(token->value[(*var)->i + (*var)->len])
			&& token->value[(*var)->i + (*var)->len] != '_')
				(*var)->len++;
		if ((*var)->len > 0)
			(*var)->string = ft_strjoin((*var)->string,
					ft_substr(token->value, (*var)->i, (*var)->len));
		(*var)->i += (*var)->len;
	}
	return (0);
}

void	help_expand2(t_var **var, t_token *token, t_env *env)
{
	(*var)->len = 0;
	while (token->value[(*var)->i + (*var)->len]
		&& token->value[(*var)->i + (*var)->len] != '$'
		&& token->value[(*var)->i + (*var)->len] != ' '
		&& (ft_isalpha(token->value[(*var)->i + (*var)->len])
			|| token->value[(*var)->i + (*var)->len] == '_'))
			(*var)->len++;
	(*var)->str = ft_substr(token->value, (*var)->i, (*var)->len);
	(*var)->i += (*var)->len;
	while (env)
	{
		if (!ft_strcmp(env->env_var, (*var)->str))
		{
			if ((*var)->len > 0)
				(*var)->string = ft_strjoin((*var)->string,
						env->env_value);
				ft_free((*var)->str); //check_free
			break ;
		}
		env = env->next;
	}
}

void	handl_expand_dquotes(t_var *var)
{
	var->i = 0;
	var->string = NULL;
	while (var->token->value[var->i])
	{
		hold_string(&var, var->token);
		if (var->token->value[var->i] == '$')
		{
			if (help_expand(&var, var->token) == 2)
				continue ;
			if (help_expand1(&var, var->token) == 2)
				continue ;
			help_expand2(&var, var->token, var->env);
			var->env = var->tmp_env;
		}
	}
	if (var->string)
		((t_token *)var->tmp->data)->value = var->string;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:45:25 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/09 21:55:58 by ahaloui          ###   ########.fr       */
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
		}
		else if (tmp && token->key == DQUATES && token->is_herdoc == 0)
		{
			var.i = 0;
			var.string = NULL;
			while (token->value[var.i])
			{
				var.len = 0;
				while (token->value[var.i + var.len]
					&& token->value[var.i + var.len] != '$')
					var.len++;
				if (var.len > 0)
					var.string = ft_strjoin(var.string,
							ft_substr(token->value, var.i, var.len));
				var.i += var.len;
				if (token->value[var.i] == '$')
				{
					if (token->value[var.i + 1] == '\0'
						|| !ft_isalnum(token->value[var.i + 1]))
					{
						var.len = 1;
						while (token->value[var.i + var.len]
							&& !ft_isalnum(token->value[var.i + var.len]))
							var.len++;
						if (var.len > 0)
							var.string = ft_strjoin(var.string,
									ft_substr(token->value,
										var.i, var.len));
						var.i += var.len;
					}
					else if (token->value[var.i] == '$')
					{
						var.i++;
						if (ft_isdigit(token->value[var.i]))
						{
							var.i++;
							continue ;
						}
					}
					else if (token->value[var.i + 1]
						&& !ft_isalpha(token->value[var.i + 1])
						&& token->value[var.i + 1] != '_')
					{
						var.len = 0;
						while (token->value[var.i + var.len]
							&& !ft_isalpha(token->value[var.i + var.len])
							&& token->value[var.i + var.len] != '_')
								var.len++;
						if (var.len > 0)
							var.string = ft_strjoin(var.string,
									ft_substr(token->value, var.i, var.len));
						var.i += var.len;
					}
				var.len = 0;
					while (token->value[var.i + var.len]
						&& token->value[var.i + var.len] != '$'
						&& token->value[var.i + var.len] != ' '
						&& (ft_isalpha(token->value[var.i + var.len])
							|| token->value[var.i + var.len] == '_'))
							var.len++;
					var.str = ft_substr(token->value, var.i, var.len);
					var.i += var.len;
					while (env)
					{
						if (tmp && !ft_strcmp(env->env_var, var.str))
						{
							if (var.len > 0)
								var.string = ft_strjoin(var.string,
										env->env_value);
							break ;
						}
						env = env->next;
					}
					env = tmp_env;
				}
			}
			if (var.string)
				((t_token *)tmp->data)->value = var.string;
		}
		tmp = tmp->next;
	}
}

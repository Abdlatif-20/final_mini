/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:32:47 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/11 16:00:40 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	initiali_var(t_var ***var, t_list *args)
{
	(**var)->i = 0;
	(**var)->flag = 0;
	(**var)->flag_export = 0;
	(**var)->is_empty_str = 0;
	(**var)->is_empty_str_export = 0;
	(**var)->number_of_commands = allocate_commande(args);
}

void	skip_spaces(t_list **args, t_token *token)
{
	if (token->key == W_SPACE)
	{
		(*args) = (*args)->next;
		if ((*args))
			token = (*args)->data;
	}
}

void	check_red(t_list **args, t_token *token, t_var *var)
{
	if (token->key == RED_APP || token->key == RED_INP
		|| token->key == RED_OUT || token->key == HEREDOC
		|| token->key == RED_APP_FILE || token->key == RED_FILE
		|| token->key == FILE_INP || token->key == EOFILE
		|| token->key == FILE_INP)
	{
		var->flag++;
		(*args) = (*args)->next;
		if (*args)
			token = (*args)->data;
	}
	if (var->flag == 2)
		var->flag = 0;
}

void	commands_helper(t_list **args, t_token *token, t_var ***var)
{
	if ((*args) && (token->key == WORD || token->key == FLAG
			|| token->key == SQUATES || token->key == DQUATES
			|| token->key == VAR))
	{
		if (!(**var)->flag && token->value[0])
		{
			if (!ft_strcmp(token->value, "export"))
			{
				(**var)->flag_export = 1;
				(**var)->is_empty_str_export = 1;
			}
			(**var)->cmd[(**var)->i++] = ft_strdup(token->value);
		}
		if (token->value[0] == '\0')
		{
			(**var)->is_empty_str = 1;
		}
		(*args) = (*args)->next;
		if (*args)
			token = (*args)->data;
		(**var)->flag = 0;
	}
	(**var)->cmd[(**var)->i] = NULL;
}

char	**get_command1(t_list *args, t_var **var)
{
	t_token	*token;

	initiali_var(&var, args);
	(*var)->cmd = (char **)malloc(sizeof(char *)
			* ((*var)->number_of_commands + 1));
	if (!(*var)->cmd)
		return (NULL);
	(*var)->cmd[(*var)->number_of_commands] = NULL;
	while (args)
	{
		token = args->data;
		check_red(&args, token, *var);
		if (token->key == PIPE)
			break ;
		skip_spaces(&args, token);
		commands_helper(&args, token, &var);
	}
	return ((*var)->cmd);
}

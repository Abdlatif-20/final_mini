/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 01:21:27 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/11 12:13:52 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_white_spaces(t_list **args, t_token **token)
{
	while (*token && (*token)->key == W_SPACE)
	{
		*args = (*args)->next;
		if (*args)
			*token = (*args)->data;
	}
}

int	rederection_app(t_list *args, int *fd_out)
{
	t_token	*token;

	if (g_shell.signel_hedoc)
		return (0);
	token = args->data;
	if (token && token->key == RED_APP)
	{
		args = args->next;
		token = args->data;
		skip_white_spaces(&args, &token);
		if (token && token->key == RED_APP_FILE)
		{
			*fd_out = open(token->value, O_CREAT | O_RDWR | O_APPEND, 0777);
			args = args->next;
			if (args)
				token = args->data;
		}
		else
			return (*fd_out = 404, printf(ERR_AMBG, token->value), 1);
	}
	return (0);
}

int	rederection_in(t_list *args, int *fd_in, char **file_name)
{
	t_token	*token;

	if (g_shell.signel_hedoc)
		return (0);
	token = args->data;
	if (token && token->key == RED_INP)
	{
		args = args->next;
		if (args)
			token = args->data;
		skip_white_spaces(&args, &token);
		if (token && token->key == FILE_INP)
		{
			if (*fd_in == -1)
				return (1);
			*fd_in = open(token->value, O_RDONLY);
			*file_name = token->value;
			args = args->next;
			if (args)
				token = args->data;
		}
		else if (token->value[0] == '\0')
			return (*fd_in = 404, printf(ERR_AMBG, token->value), 1);
	}
	return (0);
}

int	check_red_error(int **fd)
{
	if (**fd == -1)
	{
		**fd = 101;
		return (101);
	}
	return (0);
}

int	rederection_out(t_list *args, int *fd_out)
{
	t_token	*token;

	if (g_shell.signel_hedoc)
		return (0);
	token = args->data;
	if (token && token->key == RED_OUT)
	{
		args = args->next;
		if (args)
			token = args->data;
		skip_white_spaces(&args, &token);
		if (token && token->key == RED_FILE)
		{
			if (token->value[0])
				*fd_out = open(token->value, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (check_red_error(&fd_out))
				return (101);
			args = args->next;
			if (args)
				token = args->data;
		}
		else
			return (*fd_out = 404, printf(ERR_AMBG, token->value), 1);
	}
	return (0);
}

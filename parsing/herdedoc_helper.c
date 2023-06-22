/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdedoc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:58:57 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/22 03:57:20 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_is_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	heredoc_help(char **input, t_list **args, t_env *env, char *name)
{
	t_var	var;

	var.tmp = NULL;
	var.flag = 0;
	var.token = ((t_token *)(*args)->data);
	if (*input && !ft_strcmp(*input, var.token->value))
		return (free(var.token->value), var.token->value = ft_strdup(name),
			var.token->key = FILE_INP, free(*input), 2);
	if (args && *input && var.token->flag_quote == 0)
	{
		if (*input && *input[0] == '$' && !check_is_quotes(*input))
			handel_expand_heredoc(*input, &var.tmp);
		else
		{
			fill_token(&var.tmp, DQUATES, *input, 0);
			var.flag = 1;
		}
		ft_expand(&var.tmp, env);
		if (!var.flag)
			ft_free(*input);
			*input = get_value_heredoc(var.tmp, *input);
		free_token_list(&var.tmp);
	}
	return (0);
}

void	add_to_buffer(char **buffer, char *input)
{
	char	*tmp;

	tmp = ft_strdup(*buffer);
	free(*buffer);
	*buffer = ft_strjoin(tmp, input);
	*buffer = ft_strjoin(*buffer, "\n");
}

int	ft_break_while(t_var *var, int *fd, char *name)
{
	(void)name;
	if (!var->input)
	{
		if (var->buffer)
			write(*fd, var->buffer, ft_strlen(var->buffer));
		ft_free(var->buffer);
		free(var->input);
		return (1);
	}
	return (0);
}

void	heredoc_helper(t_list **args, char *name, int *fd, t_env *env)
{
	t_var	var;

	var.buffer = NULL;
	while (1)
	{
		rl_event_hook = get_0;
		signal(SIGINT, handel);
		var.input = readline("> HEREDOC$ ");
		if (ft_break_while(&var, fd, name))
			break ;
		else if (heredoc_help(&var.input, args, env, name) == 2)
		{
			if (var.buffer)
			{
				write(*fd, var.buffer, ft_strlen(var.buffer));
				ft_free(var.buffer);
			}
			break ;
		}
		else if (check_sig(&var))
			break ;
		add_to_buffer(&var.buffer, var.input);
		free(var.input);
	}
}

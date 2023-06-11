/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdedoc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:58:57 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/11 12:11:28 by aben-nei         ###   ########.fr       */
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

int	heredoc_help(char **input, t_list ***args, t_env *env, char *name)
{
	t_list	*tmp;

	tmp = NULL;
	if (*input && !ft_strcmp(*input, ((t_token *)(**args)->data)->value))
	{
		((t_token *)(**args)->data)->value = ft_strdup(name);
		((t_token *)(**args)->data)->key = FILE_INP;
		free(*input);
		return (2);
	}
	if (args && *input && ((t_token *)(**args)->data)->flag_quote == 0)
	{
		if (*input && *input[0] == '$' && check_is_quotes(*input) == 0)
			fill_token(&tmp, VAR, *input, 0);
		else
			fill_token(&tmp, DQUATES, *input, 0);
		ft_expand(&tmp, env);
		*input = ft_strdup(((t_token *)tmp->data)->value);
		tmp = NULL;
	}
	return (0);
}

void	add_to_buffer(char **buffer, char *input)
{
	char	*tmp;

	tmp = ft_strdup(*buffer);
	*buffer = ft_strjoin(tmp, input);
	*buffer = ft_strjoin(*buffer, "\n");
}

int	ft_break_while(t_var var)
{
	if (!var.input)
	{
		free(var.input);
		return (1);
	}
	return (0);
}

void	heredoc_helper(t_list **args, char *name, int **fd, t_env *env)
{
	t_var	var;

	var.buffer = NULL;
	while (1)
	{
		rl_event_hook = get_0;
		signal(SIGINT, handel);
		var.input = readline("> HEREDOC$ ");
		if (ft_break_while(var))
			break ;
		else if (heredoc_help(&var.input, &args, env, name) == 2)
		{
			if (var.buffer)
				write(**fd, var.buffer, ft_strlen(var.buffer));
			break ;
		}
		else if (!var.input[0] && g_shell.signel_hedoc == 1)
		{
			rl_done = 0;
			break ;
		}
		add_to_buffer(&var.buffer, var.input);
		free(var.input);
	}
}

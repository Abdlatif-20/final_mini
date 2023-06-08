/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdedoc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:25:15 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/08 18:26:35 by aben-nei         ###   ########.fr       */
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

void	heredoc_helper(t_list **args, char *name, int **fd, t_env *env)
{
	char	*input;

	while (1)
	{
		rl_event_hook = get_0;
		signal(SIGINT, handel);
		input = readline("> HEREDOC$ ");
		if (!input)
		{
			free(input);
			break ;
		}
		if (heredoc_help(&input, &args, env, name) == 2)
			break ;
		else if (!input[0] && g_shell.signel_hedoc == 1)
		{
			rl_done = 0;
			break ;
		}
		write((**fd), input, ft_strlen(input));
		write((**fd), "\n", 1);
		free(input);
	}
}

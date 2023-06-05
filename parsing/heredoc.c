/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:00:30 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/05 18:53:35 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/minishell.h"

// function to print the list
void	print_list(t_list *list)
{
	t_token	*token;

	while (list)
	{
		token = list->data;
		printf("key: %d, value: %s\n", token->key, token->value);
		list = list->next;
	}
}

char	*generate_name(void)
{
	static int	i;
	char		*name;
	char		*num;

	name = ft_strdup("/tmp/outfile");
	num = ft_itoa(i);
	name = ft_strjoin(name, num);
	name = ft_strjoin(name, ".txt");
	i++;
	return (free(num), name);
}

int	get_0()
{
	return (0);
}
void	handel(int SIG)
{
	(void)SIG;
	rl_done = 1;
	g_shell.signel_hedoc = 1;
}
void	heredoc_helper(t_list **args, char *name, int **fd, t_env *env)
{
	(void)env;
	char	*input;
	t_list	*tmp;
	// char 	*buffer;

	tmp = NULL;
	while (1)
	{
		rl_event_hook = get_0;
		signal(SIGINT, handel);
		input = readline("> ");
		if (!input)
		{
			free(input);
			break ;
		}
		if (input && !ft_strcmp(input, ((t_token *)(*args)->data)->value))
		{
			((t_token *)(*args)->data)->value = ft_strdup(name);
			((t_token *)(*args)->data)->key = FILE_INP;
			free(input);
			break ;
		}
		if (args && input && ((t_token *)(*args)->data)->flag_quote == 0 && input[0] == '$')
		{
			fill_token(&tmp, VAR, input, 0);
			ft_expand(&tmp, env);
			input = ft_strdup(((t_token *)tmp->data)->value);
		}
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

void	ft_heredoc(t_list *args, int *fd, char **file, t_env *env)
{
	char	*name;

	while (args)
	{
		if (g_shell.signel_hedoc)
			break ;
		if (((t_token *)args->data)->key == HEREDOC)//check
		{
			name = generate_name();
			(*fd) = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
			*file = ft_strdup(name);
			((t_token *)args->data)->key = RED_INP;
			((t_token *)args->data)->value = ft_strdup("<");
			if ((*fd) == -1)
				return ;
			args = args->next;
			if (!args)
				break ;
			if (((t_token *)args->data)->key == W_SPACE)
					args = args->next;
			heredoc_helper(&args, name, &fd, env);
			free(name);
		}
		args = args->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:17:08 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/01 09:47:22 by aben-nei         ###   ########.fr       */
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
	static int	i = 0;
	char		*name;
	char		*num;

	name = ft_strdup("/tmp/outfile");
	num = ft_itoa(i);
	name = ft_strjoin(name, num);
	name = ft_strjoin(name, ".txt");
	i++;
	return (name);
}

void	heredoc_helper(t_list **args, char *name, int **fd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (ft_strcmp(input, ((t_token *)(*args)->data)->value) == 0)
		{
			((t_token *)(*args)->data)->value = ft_strdup(name);
			((t_token *)(*args)->data)->key = FILE_INP;
			free(input);
			break ;
		}
		write((**fd), input, ft_strlen(input));
		write((**fd), "\n", 1);
		free(input);
	}
}

void	ft_heredoc(t_list *args, int *fd, char **file)
{
	char	*name;

	while (args)
	{
		if (((t_token *)args->data)->key == HEREDOC)
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
			heredoc_helper(&args, name, &fd);
			free(name);
		}
			args = args->next;
	}
}

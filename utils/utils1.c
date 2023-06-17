/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:06:45 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/15 02:24:39 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2 || !*s1 || !*s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*get_value(t_export **head_ex, char *var)
{
	t_export	*tmp;
	char		*value;

	tmp = *head_ex;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->export_var, var))
		{
			value = ft_strdup(tmp->export_value);
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_is_empty_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	free_pipefd(int **pipefd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		free(pipefd[i]);
		i++;
	}
	free(pipefd);
}

int	count_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cmd_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:51:45 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/16 02:11:39 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_commande(char *command)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	i = 0;
	start = 0;
	end = 0;
	if (!command)
		return (NULL);
	while (command[i])
	{
		if (command[i] == '/')
		{
			i++;
			while (command[i] && command[i] != '/')
				i++;
			start = i + 1;
			while (command[i])
				i++;
			end = i;
			str = ft_substr(command, start, end);
		}
	}
	return (str);
}

char	**get_cmd(char *command, char **split_paths)
{
	if ((command && command[0] == '/')
		|| (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, F_OK | X_OK) != 0)
		{
			print_error_file(command);
			exit(EXIT_FAILURE);
		}
		split_paths = malloc(sizeof(char *) * 2);
		if (!split_paths)
			return (NULL);
		split_paths[1] = NULL;
		split_paths[0] = ft_strdup(command);
	}
	return (split_paths);
}

char	**join_path_command(char *command, t_export **head_ex)
{
	char	*path;
	char	**split_paths;
	int		i;

	split_paths = NULL;
	split_paths = get_cmd(command, split_paths);
	if (split_paths)
		return (split_paths);
	path = get_value(head_ex, "PATH");
	if (!path)
		return (NULL);
	split_paths = ft_split(path, ':');
	i = -1;
	while (split_paths[++i])
	{
		split_paths[i] = ft_strjoin(split_paths[i], "/");
		if (command && command[0] == '/')
			split_paths[i] = ft_strjoin(split_paths[i], get_commande(command));
		else
			split_paths[i] = ft_strjoin(split_paths[i], command);
	}
	return (free(path), split_paths);
}

int	is_builin(t_cmd *commands)
{
	if (!ft_strcmp(commands->main_cmd, "echo"))
		return (1);
	else if (!ft_strcmp(commands->main_cmd, "cd"))
		return (1);
	else if (!ft_strcmp(commands->main_cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(commands->main_cmd, "export"))
		return (1);
	else if (!ft_strcmp(commands->main_cmd, "unset"))
		return (1);
	else if (!ft_strcmp(commands->main_cmd, "env"))
		return (1);
	else if (!ft_strcmp(commands->main_cmd, "exit"))
		return (1);
	return (0);
}

char	*check_if_command_found(char *command, t_export **head_ex)
{
	char	**split_paths;
	char	*str;
	int		i;

	split_paths = NULL;
	if (head_ex && *head_ex)
	{
		split_paths = join_path_command(command, head_ex);
		if (!split_paths)
			return (free_split_paths(split_paths), NULL);
		i = 0;
		while (split_paths[i])
		{
			if (access(split_paths[i], F_OK | X_OK) == 0)
			{
				str = ft_strdup(split_paths[i]);
				return (str);
			}
			i++;
		}
	}
	return (free_split_paths(split_paths), NULL);
}

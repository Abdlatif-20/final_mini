/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cmd_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:35:00 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/10 14:57:19 by ahaloui          ###   ########.fr       */
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

char	**check_command(char *command, char ***split_paths)
{
	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, F_OK | X_OK) != 0)
		{
			printf("minishell: %s: No such file or directory\n", command);
			g_shell.exit_status = EXIT_FAILURE;
			exit(g_shell.exit_status);
		}
		split_paths = malloc(sizeof(char *) * 2);
		if (!split_paths)
			return (NULL);
		*split_paths[0] = ft_strdup(command);
		return (*(split_paths));
	}
	return (NULL);
}

char	**join_path_command(char *command, t_export **head_ex)
{
	char	*path;
	char	**split_paths;
	int		i;
	int		j;

	if (check_command(command, &split_paths))
		return (split_paths);
	path = get_value(head_ex, "PATH");
	if (!path)
		return (NULL);
	split_paths = ft_split(path, ':');
	i = 0;
	while (split_paths[i])
	{
		j = 0;
		split_paths[i] = ft_strjoin(split_paths[i], "/");
		if (command[j] == '/')
			split_paths[i] = ft_strjoin(split_paths[i], get_commande(command));
		else
			split_paths[i] = ft_strjoin(split_paths[i], command);
		i++;
	}
	return (split_paths);
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
	int		i;

	if (head_ex && *head_ex && command)
	{
		split_paths = join_path_command(command, head_ex);
		if (!split_paths)
			return (NULL);
		i = 0;
		while (split_paths[i])
		{
			if (access(split_paths[i], F_OK | X_OK) == 0)
				return (split_paths[i]);
			i++;
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:19:03 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/08 23:37:30 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	print_list1(t_list *cmd)
{
	if (!cmd)
		return ;
	t_list *tmp = cmd;
	t_token *token = cmd->data;
	while (tmp)
	{
		token = tmp->data;
		printf("key = [%d] | value = [%s]\n", token->key, token->value);
		tmp = tmp->next;
	}
}
void	print_list11(t_list *cmd)
{
	if (!cmd)
		return ;
	t_list *tmp = cmd;
	t_cmd *token = cmd->data;
	while (tmp)
	{
		int	i = 0;
		token = tmp->data;
		while (tmp && token->cmds[i] && token->cmds)
		{
			printf("cmd = [%s]\n",token->cmds[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

// char **new_env(char **env)
// {
// 	char **new_env;
// 	int i = 0;
// 	while (env[i])
// 		i++;
// 	new_env = (char **)malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while (env[i])
// 	{
// 		new_env[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	new_env[i] = NULL;
// 	return (new_env);
// }

void add_export_ignored(t_info *info)
{
	ft_lst_add_back_export(&info->head_ex, ft_lst_new_export("PWD", getcwd(NULL, 0)));
	ft_lst_add_back_export(&info->head_ex, ft_lst_new_export("SHLVL", "1"));
	ft_lst_add_back_export(&info->head_ex, ft_lst_new_export("_", ft_strjoin(ft_strdup(getcwd(NULL, 0)), "./minishell")));
	ft_lst_add_back_export(&info->head_ex, ft_lst_new_export("OLDPWD", ft_strdup("")));
	ft_lst_add_back_export(&info->head_ex, ft_lst_new_export("PATH", "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"));
}

void	add_env_ignored(t_info *info)
{
	ft_lst_add_back_env(&info->head_en, ft_lst_new_env("PWD", getcwd(NULL, 0)));
	ft_lst_add_back_env(&info->head_en, ft_lst_new_env("SHLVL", "1"));
	ft_lst_add_back_env(&info->head_en, ft_lst_new_env("_", ft_strjoin(ft_strdup(getcwd(NULL, 0)), "/./minishell")));
	ft_lst_add_back_env(&info->head_en, ft_lst_new_env("OLDPWD", ft_strdup("")));
	ft_lst_add_back_env(&info->head_en, ft_lst_new_env("PATH", "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"));
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_list	*args;
	t_list	*cmd;
	t_info	*info;
	// char	**env1;

	(void)argc;
	(void)argv;
	info = NULL;
	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
		return (0);
	args = NULL;
	cmd = NULL;
	input = NULL;
	info->head_ex = NULL;
	info->head_en = NULL;
	if (env == NULL || *env == NULL)
	{
		add_export_ignored(info);
		add_env_ignored(info);
	}
	fill_export_list(env, &info->head_ex);
	fill_env_list(env, &info->head_en);

	// *********************************************
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	// *********************************************


	g_shell.path = get_path_home(&info->head_ex);
	printf("\033[2J\033[1;1H");
	while (42)
	{
		rl_catch_signals = 0;
		g_shell.signel_hedoc = 0;
		input = readline("-> minishell$ ");
		if (input)
		{
			add_history(input);
			if (check_quotes(input))
			{
				free(input);
				printf("minishell: quotes not closed\n");
				continue ;
			}
			get_token(input, &args);
			if (args && syntex_error(args))
			{
				ft_lstclear(&args);
				continue ;
			}
			ft_trim_quotes(&args);
			ft_expand(&args, info->head_en);
			ft_join_args(&args);
			command_table(args, &cmd, info->head_en);
			// print_list11(cmd);
			if (cmd && cmd->data && g_shell.signel_hedoc == 0)//check
				choose_command(cmd, info);
			ft_lstclear(&args);
			ft_lstclear(&cmd);
			// free_token_list(&args);
			// free_list_cmd(&cmd);
			free (input);
		}
		else
		{
			free(input);
			printf(" exit\n");
			break ;
		}
	}
	return (0);
}

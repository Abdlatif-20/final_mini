/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:15:42 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/05 16:58:21 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
while true; do
  leaks minishell
  sleep 1
done
*/

#include "../include/minishell.h"
// #include "../libft/libft.h"

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
		while (token->cmds[i])
		{
			printf("cmd = [%s]\n",token->cmds[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_list	*args;
	t_list	*cmd;
	t_info	*info;
	char	**env1;

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
		// uid_t uid = getuid();
		// struct passwd *pw = getpwuid(uid);
		env1 = (char **)malloc(sizeof(char *) * 5);
		env1[0] = ft_strjoin(ft_strdup("PWD=/Users/ahaloui"), "pw->pw_name");
		env1[1] = ft_strdup("SHLVL=1");
		env1[2] = ft_strdup("_=/usr/bin/env"); // env
		env1[2] = ft_strjoin(ft_strdup("OLDPWD=/Users/ahaloui"), "pw->pw_name"); //export 
		env1[3] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin");// export/env
		env = env1;
	}

	fill_export_list(env, &info->head_ex);
	fill_env_list(env, &info->head_en);

	// *********************************************
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	// *********************************************


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

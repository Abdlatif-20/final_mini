
#include "../include/minishell.h"
int g_exit_status = 0;

void help(int status)
{
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		printf("g_exit_status = %d\n", g_exit_status);
	}
	else if (WIFSIGNALED(status))
	{
		int signal_number = WTERMSIG(status);
		g_exit_status = 128 + signal_number;
		if (signal_number == SIGKILL)
			printf("Child process terminated by kill signal (SIGKILL)\n");
		else if (signal_number == SIGSEGV)
			printf("Child process terminated by segmentation fault (SIGSEGV)\n");	
		else if (signal_number == SIGINT)
			printf("Child process terminated by Ctrl+C\n");
		else if (signal_number == SIGTERM)
			printf("Child process terminated by SIGTERM\n");
		else if (signal_number == SIGQUIT)
			printf("Child process terminated by SIGQUIT\n");
		else if (signal_number == SIGTSTP)
			printf("Child process terminated by Ctrl+Z (SIGTSTP)\n");
		else if (signal_number == SIGPIPE)
			printf("Child process terminated by broken pipe (SIGPIPE)\n");
		else if (signal_number == SIGCHLD)
			printf("Child process terminated by child process (SIGCHLD)\n");
		else if (signal_number == SIGCONT)
			printf("Child process terminated by continuing after Ctrl+Z (SIGCONT)\n");
		else if (signal_number == SIGSTOP)
			printf("Child process terminated by stop signal (SIGSTOP)\n");
		else if (signal_number == SIGTTIN)
			printf("Child process terminated by background process attempting read (SIGTTIN)\n");
		else if (signal_number == SIGTTOU)
			printf("Child process terminated by background process attempting write (SIGTTOU)\n");
		else if (signal_number == SIGHUP)
			printf("Child process terminated by hangup signal (SIGHUP)\n");
		else if (signal_number == SIGXCPU)
			printf("Child process terminated by CPU time limit exceeded (SIGXCPU)\n");
		else if (signal_number == SIGXFSZ)
			printf("Child process terminated by file size limit exceeded (SIGXFSZ)\n");
		else if (signal_number == SIGALRM)
			printf("Child process terminated by alarm clock (SIGALRM)\n");
		else if (signal_number == SIGPROF)
			printf("Child process terminated by profiling timer expired (SIGPROF)\n");
		else if (signal_number == SIGUSR1)
			printf("Child process terminated by user-defined signal 1 (SIGUSR1)\n");
		else if (signal_number == SIGUSR2)
			printf("Child process terminated by user-defined signal 2 (SIGUSR2)\n");
		else if (signal_number == SIGIO)
			printf("Child process terminated by I/O now possible (SIGIO)\n");
		else
			printf("Child process terminated by signal: %d\n", signal_number);
		printf("g_exit_status = %d\n", g_exit_status);
	}
}

char	*get_commande(char *command)
{
	int	i;
	int start;
	int end;
	char *str;

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

char  **join_path_command(char *command, t_export **head_ex)
{
	char *path;
	char **split_paths;
	int i;
	int j;
	
	if (command[0] == '/' || command[0] == '.')
	{
		split_paths = malloc(sizeof(char *) * 2);
		split_paths[0] = ft_strdup(command);
		return (split_paths);
	}
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

int is_builin(t_cmd *commands)
{
	if (ft_strcmp(commands->main_cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(commands->main_cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(commands->main_cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(commands->main_cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(commands->main_cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(commands->main_cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(commands->main_cmd, "exit") == 0)
		return (1);
	return (0);
}

char  *check_if_command_found(char *command, t_export **head_ex)
{
	char **split_paths;
	int i;

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
#include "../include/minishell.h"

t_shell g_shell;


void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		printf("\nCtrl+D (EOF) received. Exiting...\n");
		exit(0);
	}
}

void handle_specific_signal_1(int signal_number)
{
    if (signal_number == SIGCONT)
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
}
void handle_specific_signal(int signal_number)
{
    if (signal_number == SIGABRT)
        printf("Child process terminated by abort signal (SIGABRT) %d\n", signal_number);
    else if (signal_number == SIGKILL)
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
    else
        handle_specific_signal_1(signal_number);
}

void handle_signal_status(int status)
{
    int signal_number;

    if (WIFSIGNALED(status))
    {
        puts("2222\n");
        signal_number = WTERMSIG(status);
        g_shell.exit_status = 128 + signal_number;
        printf("the exit status isssssss %d\n", g_shell.exit_status);
        handle_specific_signal(signal_number);
    }
}

void handle_exit_status(int status)
{
    if (WIFEXITED(status))
    {
        puts("111\n");
        g_shell.exit_status = WEXITSTATUS(status);
        // printf("the exit status is %d\n", g_shell.exit_status);
    }
}

void display_status_code(int status)
{
    handle_exit_status(status);
    handle_signal_status(status);
}

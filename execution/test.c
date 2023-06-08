#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#define READ_END 0
#define WRITE_END 1
// void handle_sigint(int sig) {
//     rl_on_new_line();  // Move cursor to new line
//     rl_replace_line("Ctrl-C detected. Press enter to continue.", 0);  // Replace input line
//     rl_redisplay();  // Redisplay prompt and new line
// }

// int main() {
//     signal(SIGINT, handle_sigint);  // Set up signal handler
//     char* input;
//     while (1) {
//         input = readline("Enter some text: ");
//         if (!input) {  // User entered EOF
//             break;
//         }
//         printf("You entered: %s\n", input);  // Process user input
//         free(input);
//     }
//     return 0;
// }

int main() {
    // Commands to execute
    char *commands[] = {"ls", "-l", "|", "grep", "test", "|", "wc", "-l", NULL};
    int num_commands = sizeof(commands) / sizeof(commands[0]) - 1;
    
    // Create pipes
    int pipes[num_commands - 1][2];
    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
    
    // Execute commands with pipes
    int i = 0;
    int in_fd = STDIN_FILENO;
    int out_fd;
    while (i < num_commands) {
        // Create child process
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0) { // Child process
            if (i < num_commands - 1) { // Not the last command
                if (dup2(pipes[i][WRITE_END], STDOUT_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }
            
            if (i > 0) { // Not the first command
                if (dup2(in_fd, STDIN_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }
            
            // Close all pipe ends
            for (int j = 0; j < num_commands - 1; j++) {
                close(pipes[j][READ_END]);
                close(pipes[j][WRITE_END]);
            }
            
            // Execute command
            char **args = malloc((i == num_commands - 1 ? i : i + 1) * sizeof(char *));
            int k = 0;
            while (strcmp(commands[k], "|") != 0) {
                args[k] = commands[k];
                k++;
            }
            args[k] = NULL;
            
            execve(args[0], args, NULL);
            
            // Execution should not reach here unless there is an error
            perror("execve");
            exit(EXIT_FAILURE);
        }
        
        // Parent process
        if (i > 0) { // Not the first command
            close(in_fd);
        }
        
        if (i < num_commands - 1) { // Not the last command
            close(pipes[i][WRITE_END]);
            in_fd = pipes[i][READ_END];
        }
        
        i++;
    }
    
    // Close remaining pipe ends
    for (int i = 0; i < num_commands - 1; i++) {
        close(pipes[i][READ_END]);
        close(pipes[i][WRITE_END]);
    }
    
    // Wait for all child processes to terminate
    while (wait(NULL) != -1);
    return 0;
}
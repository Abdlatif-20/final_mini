/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:59:42 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/11 02:17:28 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
#include <pwd.h>
#include <limits.h>
// # include <glob.h>

# define ERR_UNX_TNKN "minishell: syntax error near unexpected token `|'\n"
# define ERR_TK "minishell: syntax error near unexpected token `%s'\n"
# define ERR_NL "minishell: syntax error near unexpected token `newline'\n"
# define CHECK_SYMBOL "$\"'+-./:;<=>@[\\]^`{|}~%#&()*,;=[]"
# define ERR_ARG "minishell: can't open input file: %s\n"
# define ERR_AMBG "minishell: %s: ambiguous redirect\n"
# define MAX_LL 9223372036854775807
# define MIN_LL -9223372036854775808

// int g_exit_status;

enum e_type
{
	FLAG,
	WORD,
	DQUATES,
	SQUATES,
	PIPE,
	RED_OUT,
	RED_INP,
	RED_APP,
	W_SPACE,
	HEREDOC,
	EOFILE,
	RED_APP_FILE,
	RED_FILE,
	FILE_INP,
	VAR,
};

# define READ_END 0
# define WRITE_END 1

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;


typedef struct s_token
{
	int			key;
	char		*value;
	int			flag_quote;
	int			is_herdoc;
}					t_token;

typedef struct g_shell
{
	int		exit_status;
	int		signel_hedoc;
	int		signel_cat;
	char	*path;
}				t_shell;

extern t_shell g_shell;

typedef struct s_cmd
{
	char		**cmds;
	int			fd_in;
	int			fd_out;
	char		*main_cmd;
	char		*file_name;
	int			heredoc;
}					t_cmd;

typedef struct s_init
{
	int		ac;
	char	**av;
	char	**environ;
}	t_init;

typedef struct s_env
{
	char			*env_var;
	char			*env_value;
	struct s_env	*next;
}				t_env;

typedef struct s_export
{
	char				*export_var;
	char				*export_value;
	struct s_export		*next;
}				t_export;

typedef struct t_var
{
	int		i;
	int		j;
	int		flag;
	int		fd_in;
	int		fd_out;
	int		heredoc;
	char	*file_name;
	int		len;
	char	*str;
	char	**cmd;
	int		is_empty_str;
	char	*string;
	int		start;
	int		end;
	int		number_of_commands;
	t_list	*tmp;
	t_env	*tmp_env;
	char	*temp;
	char	*input;
	char	*buffer;
}				t_var;

typedef struct s_info
{
	t_env		*head_en;
	t_export	*head_ex;
	int			exit_status;
	int			in;
	int			out;
	t_cmd		*commands;
	pid_t		pid;
	char		*temp;
	int			i;
	t_var		*var;
}			t_info;

char		**create_env(t_info *info);
void 		help(int status);
// file my_echo.c
// int			my_echo(t_cmd *cmd);
int			my_echo(t_cmd *cmd);
int			check_option(char *cmd);
char		*get_last_split(t_cmd *cmd);

// file my_pwd.c
int			my_pwd(t_info *info);

// file my_cd.c
char		*get_path_home(t_export **head_ex);
char		*get_old_path(t_export **head_ex);
char		*get_path(t_export **head_ex);
void		set_value(t_export **head_ex, char *export_var, char *new_value);
void		init_pwd(t_export **head_ex);
int			get_pos(char *str, char c);
int			my_cd(t_cmd *commands, t_info *info);

// file my_export.c
t_export	*ft_lst_new_export(char *export_var, char *export_value);
void		ft_lst_add_back_export(t_export **head_ex, t_export *new);
char		*get_export_variable(char *variable);
char		*get_export_value(char *value);
void		add_export_element(char *export_var, char *export_value,
				t_export **head_ex);
void		print_list_export(t_info *info);
void		sort_export_list(t_export **head_ex);
int			check_is_empty_string(char *str);
int			check_if_export_var_exist(t_export *head_ex, char *export_var);
void		remove_export_element(t_export **head_ex, char *export_var);
void		fill_export_list(char **environ, t_export **head_ex);


// file my_unset.c
void		my_unset(t_cmd *commands, t_info *info);

// file my_exit.c
// int			my_exit(void);
int my_exit(t_cmd *commands);

// file utils1.c
char		*get_value(t_export **head_ex, char *var);

void		execute_commande(t_cmd *commands, t_info *info, t_list *shell, t_var *var);

// file utils3.c
void		execute_commands_with_pipe(t_list *cmd, t_info *info, int nb_pipes, t_var *var);

// file help_export.c
int			check_export(char **split, t_var *var);
void		concatenation_export(t_export **head_ex, char *export_variable,
				char *new_value);
void		add_export(t_export **head_ex, char **split);
int			check_if_valid_args(char *split);

// file help_env.c
void		add_env(t_env **head, char **split);
void		concatenation_env(t_env **head_en, char *env_var, char *new_value);
//

// help_cmd_simple.c
char		*get_commande(char *command);
char		**join_path_command(char *command, t_export **head_ex);
char		*check_if_command_found(char *command, t_export **head_ex);
int			is_builin(t_cmd *commands);

// utils_error.c
void		print_error_cmd(char *command);
void		print_error_file(char *command);
void		print_error_fork(void);

/*--------------- libft ------------------------*/
int			ft_isalpha(int c);
int			ft_isdigit(int c );
int			ft_isalnum(int c);
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);
long long	ft_atoi(char *str);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
void		*ft_memset(void *str, int c, size_t n);
void		ft_bzero(void *s, size_t n);

/*--------------- list ------------------------*/
t_list		*ft_lstnew(void	*content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst);
/*-----------------------------------------------*/
void		ft_heredoc(t_list *args, int *fd, char **file, t_env *env);
void		heredoc_helper(t_list **args, char *name, int **fd, t_env *env);
int			heredoc_help(char **input, t_list ***args, t_env *env, char *name);
int			get_0(void);
void		handel(int SIG);
/*---------------------- token --------------------*/
void		get_token(char *input, t_list **token);
void		fill_white_space(char *input, t_list **token, t_var **var);
void		get_flags(char *input, t_list **token, t_var *var);
void		check_quote(char *input, t_list **token, t_var *var, int len);
void		check_word(char *input, t_list **token, t_var *var, int len);
void		check_pipe(char *input, t_list **token, int *i, int *flag);
void		check_variable(char *input, t_list **token, int *i);
/*-----------------------------------------------------*/

int			syntex_error(t_list *list);
int			check_quotes(char *input);
void		fill_env_list(char **environ, t_env **head_env);
int			ft_strcmp(char *s1, char *s2);
void		ft_trim_quotes(t_list **args);
void		ft_join_args(t_list **args);
/*--------------------------------------------------------*/
void		ft_expand(t_list **list, t_env *env);
int			handel_var(t_token **token, t_var *var, t_env *env);
int			ft_expender_help(t_token ***token,
				t_env *env, t_var **var);
char		*get_variable_name(char *name);
void		free_array(char **array);
/*--------------------------------------------------------*/
void		ft_remove_node(t_list **head, t_list *node);
char		*skip_whitespace(char *input);
int			ft_whitespace(char c);
int			rederection_out(t_list *args, int *fd_out);
int			rederection_in(t_list *args, int *fd_in, char **file_name);
int			rederection_app(t_list *args, int *fd_out);
void		fill_token(t_list **args, int token, char *word, int is_heredoce);
void		fill_cmd(t_list **cmd, t_var var, char **args, int heredoc);
void		command_table(t_list *args, t_list **cmd, t_env *env, t_var *var);
int			allocate_commande(t_list *args);
char		**get_command1(t_list *args, t_var **var);
void		free_token_list(t_list **list);
void		free_list_cmd(t_list **list);

// utils
// int		count_words_me(char *str, char c);
void		choose_command(t_list *shell, t_info *info, t_var *var);
void		builtin_execution(t_list *shell, t_info *info, int flag, t_var *var);

// signals_and_status_code.c
void		handle_specific_signal_1(int signal_number);
void		handle_specific_signal(int signal_number);
void		handle_signal_status(int status);
void		handle_exit_status(int status);
void		display_status_code(int status);
void		signal_handler(int sig);


long long	ft_atoi1(char *str, int *flag);

// help_cd_functions.c
void	set_value1(t_info *info, char *env_var, char *new_value);
char	*get_value2(t_info *info, char *env_var);
int		if_there_is_tilda(char *cmd);
int		case_of_tilda_in_path(t_info *info, char *path_tmp1);
int		case_of_remove_directory(t_cmd *commands, t_info *info, char **tmp, int i);

// check_args.c
int check_is_contain(char *split);
int check_if_valid_args(char *split);
char *get_arg(char *arg);
// int  check_export(char **split);


// file my_env.c
char		*get_env_variable(char *variable);
char		*get_env_value(char *value);
void		add_env_element(char *env_var, char *env_value, t_env **head_en);

int			check_is_empty_string_env(char *str);
int			check_if_env_var_exist(t_env *head_en, char *env_var);
void		remove_env_element(t_env **head_en, char *env_var);
void		fill_env_list(char **environ, t_env **head_env);


// help_env_1.c
t_env	*ft_lst_new_env(char *env_var, char *env_value);
void	ft_lst_add_back_env(t_env **head_en, t_env *new);
void 	remove_env_element(t_env **head_en, char *env_var);
void	add_env_element(char *env_var, char *env_value, t_env **head_en);
void	print_list_env(t_info *info);


//utils6.c
char	**create_env(t_info *info);
void	execute1(t_list *cmd, t_info *info, t_var *var);
void	execute2(t_info *info);
void	execute3(t_info *info, t_list *cmd, int **pipefd, int nb_pipes, t_var *var);
void	if_herdoc(t_cmd *commands);


//utils7.c
int		**create_pipefd(int nb_pipes);
void	create_pipe(int pipefd[2]);
void	close_pipe(int **pipefd, int nb_pipes);
void	wait_for_child(int nb_pipes);
int		get_nbr_node(t_list *shell);

// execute_multi_command.c
void	merge_dup_pipe_herdoc(int **pipefd, int i, int nb_pipes, t_cmd *commands);

void	reserve_list(t_info *info);


#endif

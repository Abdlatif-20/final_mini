# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 17:36:22 by aben-nei          #+#    #+#              #
#    Updated: 2023/06/08 14:05:56 by ahaloui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLDMAGENTA=\033[1;35m
BOLDYELLOW=\033[1;33m
RESET=\033[0m
YEAR=$(shell date +'%Y')
# Color definitions
GREEN = \033[0;32m
NC = \033[0m

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address 
#  -Wno-misleading-indentation
# -fsanitize=address
RFLAGS = -lreadline

# SRC built_in
SOURCE_BUILT_IN = execution/built_in_functions/my_export.c execution/built_in_functions/my_env.c execution/built_in_functions/my_unset.c \
				execution/built_in_functions/my_pwd.c execution/built_in_functions/my_cd.c execution/built_in_functions/my_echo.c execution/built_in_functions/my_exit.c

# source files
SRC_EXEC = utils/execution.c utils/signals_and_status_code.c utils/utils5.c utils/utils1.c utils/utils_error.c \
			utils/help_cmd_simple.c utils/execute_simple_command.c utils/execute_multiple_command.c \
			execution/help_export.c execution/help_env.c execution/help_cd.c $(SOURCE_BUILT_IN)
# libft
LIB = libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_strlen.c \
	libft/ft_strchr.c libft/ft_atoi.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_split.c\
	libft/ft_itoa.c libft/ft_putstr_fd.c libft/ft_lstnew.c libft/ft_lstadd_front.c libft/ft_lstsize.c\
	libft/ft_lstlast.c libft/ft_lstadd_back.c libft/ft_lstclear.c libft/ft_strlcpy.c libft/ft_bzero.c libft/ft_memset.c
# SRC parsing
SRCS = main/main.c parsing/ft_trim_quotes.c parsing/join_args.c utils/help_command_table.c parsing/ft_expand.c parsing/token.c utils/utils.c parsing/ft_token.c parsing/syntex_error.c\
	parsing/check_quotes.c parsing/rederection.c parsing/heredoc.c parsing/command_table.c parsing/heredoc_helper.c parsing/expand_helper.c parsing/expand_dquotes.c utils/utils4.c $(SRC_EXEC) $(LIB)

OBJS = $(SRCS:.c=.o)


RL_INC = -I $(shell brew --prefix readline)/include
RL_LIB = -L $(shell brew --prefix readline)/lib

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(RFLAGS) $(RL_LIB) $(OBJS) -o $(NAME)
	@clear
	@echo "\033[32m[OK] \033[0mCompilation done"
	@printf "$(BOLDMAGENTA)"
	@printf " __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
	@printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
	@printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
	@printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
	@printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
	@printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$(RESET)"
	@echo
	@printf "$(BOLDYELLOW)"
	@printf "                          Copyright (c) $(YEAR) NO_NAME, ahaloui\n"
	@printf "$(RESET)"
	@echo

%.o: %.c include/minishell.h
	@$(CC) $(CFLAGS) $(RL_INC) -c $< -o $@
	@clear
	@printf "$(BOLDMAGENTA)"
	@printf " __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
	@printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
	@printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
	@printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
	@printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
	@printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$(RESET)"
	@echo
	@printf "$(BOLDYELLOW)"
	@printf "                          Copyright (c) $(YEAR) NO_NAME, ahaloui\n"
	@printf "$(RESET)"
	@echo
	@echo "$(GREEN)Compiled $<$(NC)"
	@sleep 0.05

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	@clear
	@echo "\033[32m[OK] \033[0mCleaning done"

re: fclean all


# banner:
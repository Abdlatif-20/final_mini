# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 19:31:00 by aben-nei          #+#    #+#              #
#    Updated: 2023/06/05 16:41:44 by ahaloui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


BOLDMAGENTA=\033[1;35m
BOLDYELLOW=\033[1;33m
RESET=\033[0m
YEAR=$(shell date +'%Y')

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -Wno-misleading-indentation -fsanitize=address
#  -Wno-misleading-indentation
# flag sanitiz 
# -fsanitize=address -g3 -fno-omit-frame-pointer
RFLAGS = -lreadline

SOURCE_BUILT_IN = execution/built_in_functions/my_export.c execution/built_in_functions/my_env.c execution/built_in_functions/my_unset.c \
				execution/built_in_functions/my_pwd.c execution/built_in_functions/my_cd.c execution/built_in_functions/my_echo.c execution/built_in_functions/my_exit.c

# source files
SRC_DYALI = utils/execution.c utils/signals_and_status_code.c utils/utils5.c utils/utils1.c utils/utils_error.c utils/help_cmd_simple.c utils/execute_simple_command.c utils/execute_multiple_command.c execution/help_export.c execution/help_env.c $(SOURCE_BUILT_IN)


SRCS = main/main.c parsing/ft_trim_quotes.c parsing/join_args.c utils/help_command_table.c parsing/ft_expand.c parsing/token.c utils/utils.c parsing/ft_token.c parsing/syntex_error.c\
	parsing/check_quotes.c parsing/rederection.c parsing/heredoc.c parsing/command_table.c $(SRC_DYALI)

OBJS = $(SRCS:.c=.o)

LIB = libft/libft.a

RL_INC = -I $(shell brew --prefix readline)/include
RL_LIB = -L $(shell brew --prefix readline)/lib

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $(RFLAGS) $(RL_LIB) $(OBJS) $(LIB) -o $(NAME)
	@echo -e "\033[32m[OK] \033[0mCompilation done"
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

%.o: %.c include/minishell.h
	$(CC) $(CFLAGS) $(RL_INC) -c $< -o $@
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

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	@clear
	@echo -e "\033[32m[OK] \033[0mCleaning done"

re: fclean all


# banner:
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 16:02:47 by gpouzet           #+#    #+#              #
#    Updated: 2023/10/28 11:19:57 by lvincent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		=	clang

FLAGS 	=	-Wall -Wextra -Werror

NAME 	=	minishell

SRC 	=	src/small_builtins.c src/g_env.c src/ft_echo.c src/main.c src/parserv2.c\
			src/parser.c src/pars_redir.c src/arg_sep.c src/t_data.c src/env_sep.c \
			src/exec.c src/export.c src/redirections.c src/pipeline.c src/heredoc.c\
			src/utils.c src/utils2.c src/utils3.c src/ft_exit.c src/signal.c src/quote.c\
			 src/error.c src/ft_export.c src/exception.c

OBJ	= $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $<
	@echo -n "\\r\033[2K"
	@echo -n "\\r\033[1;33m[compiling...]"$<

all: $(NAME)


$(NAME): $(OBJ)
	@make -s --no-print-directory -C libft
	@$(CC) $(FLAGS) $(OBJ) -lreadline -L./libft -lft -o $(NAME)
	@echo -n "\\r\033[2K"
	@echo "\033[1;32m[executable created]"


clean:
	@make fclean --no-print-directory -C libft
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;32m[Programe deleted]"

re: fclean all

debug: FLAGS += -g
debug: fclean $(OBJ)
	@make debug_lib -s --no-print-directory -C libft
	@$(CC) $(FLAGS) -g $(OBJ) -lreadline -L./libft -lft -o $(NAME)
	@echo -n "\\r\033[2K"
	@echo "\033[1;32m[executable created]"

.PHONY: all clean fclean re debug

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 16:02:47 by gpouzet           #+#    #+#              #
#    Updated: 2023/10/17 13:17:38 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		=	clang

FLAGS 	=	-Wall -Wextra -Werror -g

NAME 	=	minishell

SRC 	=	src/small_builtins.c src/g_env.c src/ft_echo.c src/main.c src/parserv2.c\
			src/parser.c src/arg_sep.c src/t_data.c src/env_sep.c src/exec.c src/export.c\
			src/redirections.c src/utils.c src/utils2.c  src/pipeline.c 

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
	@rm -rf $(OBJ) $(OBJB)

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;32m[Programe deleted]"

re: fclean all

.PHONY: all clean fclean re

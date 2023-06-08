# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 16:01:39 by gpouzet           #+#    #+#              #
#    Updated: 2023/04/14 13:26:39 by gpouzet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
FLAGS = -Wall -Wextra -Werror 

NAME = libft.a

SRC 	=	libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c \
			libft/ft_isprint.c libft/ft_toupper.c libft/ft_tolower.c libft/ft_isnumber.c \
			libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c \
			libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memmove.c \
			libft/ft_strlen.c libft/ft_strlcpy.c libft/ft_strlcat.c \
			libft/ft_strchr.c libft/ft_strrchr.c libft/ft_strncmp.c \
			libft/ft_strnstr.c libft/ft_calloc.c libft/ft_strdup.c \
			libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c \
			libft/ft_atoi.c libft/ft_itoa.c libft/ft_substr.c \
			libft/ft_strmapi.c libft/ft_striteri.c \
			libft/ft_putchar_fd.c libft/ft_putstr_fd.c \
			libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \
			libft/ft_tabstrlen.c \

SRC 	+=	lst/ft_lstnew.c lst/ft_lstadd_front.c lst/ft_lstsize.c \
			lst/ft_lstlast.c lst/ft_lstadd_back.c lst/ft_lstdelone.c \
			lst/ft_lstclear.c lst/ft_lstiter.c lst/ft_lstmap.c \
			
SRC 	+=	printf/ft_printf.c\
			printf/ft_charsize.c printf/ft_digits.c printf/ft_hexa.c\
			printf/ft_toolsprintf.c\
			
SRC 	+=	GNL/get_next_line.c\
			
SRC		+=	stack/stack.c stack/stack_utils.c\

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo -n "\033[2K"
	@echo -n "\\r\033[1;32m[compilation completed]"

%.o: %.c
	@echo -n "\\r\033[2K"
	@echo -n "\\r\033[1;33m[compiling...]"$<
	@$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)
	@echo "\033[1;32m[object files cleaned]"

fclean: clean
	@rm -rf $(NAME) 
	@echo "\033[1;32m[Library deleted]"

re: fclean all

.PHONY: all so list clean fclean re

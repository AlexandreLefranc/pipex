# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 01:37:09 by alefranc          #+#    #+#              #
#    Updated: 2022/03/09 17:05:29 by alefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = clang
FLAGS = -Wall -Wextra -Werror -g3
INC_FLAG = -Iinclude

SRCDIR = src/
SRCFILES =	main.c \
			check_input.c \
			parse_input.c \
			plug_pipes.c \
			run_pipex.c \
			utils_calloc.c \
			utils_io.c \
			utils_lst.c \
			utils_split.c \
			utils_str.c \
			utils_strtab.c \
			utils_wrap.c
SRC = $(addprefix $(SRCDIR), $(SRCFILES))
OBJ = $(SRC:.c=.o)

HEADER = include/pipex.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INC_FLAG) $(OBJ) $(LIBFTDIR)$(LIBFT) -o $(NAME)

$(SRCDIR)%.o: $(SRCDIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $(INC_FLAG) $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

test:
	echo $(HEADER)

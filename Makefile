# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 01:37:09 by alefranc          #+#    #+#              #
#    Updated: 2022/02/01 14:30:44 by alefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFTDIR = libft/
LIBFT = libft.a

CC = clang
FLAGS = -Wall -Wextra -Werror
INC_FLAG = -Iinclude -I$(LIBFTDIR)include
# LIB_FLAG = $(LIBFTDIR)$(LIBFT)

SRCDIR = src/
SRCFILES = 	pipex.c \
			check_input.c \
			parse_input.c \
			run_pipex.c \
			pipex_utils.c
SRC = $(addprefix $(SRCDIR), $(SRCFILES))
OBJ = $(SRC:.c=.o)

HEADER = include/pipex.h

all: $(NAME)

$(NAME): $(LIBFTDIR)$(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(INC_FLAG) $(OBJ) $(LIBFTDIR)$(LIBFT) -o $(NAME)

$(LIBFTDIR)$(LIBFT):
	make -C $(LIBFTDIR)

$(SRCDIR)%.o: $(SRCDIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $(INC_FLAG) $< -o $@

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJ)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -rf $(NAME)

re: fclean all

test:
	echo $(HEADER)

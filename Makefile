# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/10 17:38:22 by dmorgil           #+#    #+#              #
#    Updated: 2018/12/12 21:14:13 by dmorgil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   ft_ls
SRC_DIR     =   ./sources
OBJ_DIR     =   ./objects
RAW_SRC     =	main.c \
				ft_vector_create.c ft_vector_to_array.c ft_vector_push_back.c \
				ft_vector_free.c ft_ceill.c ft_floorl.c \
				ft_vector_get_functions.c\

RAW_OBJS=$(RAW_SRC:.c=.o)
SRCS=$(addprefix $(SRC_DIR)/,$(RAW_SRC))
OBJS=$(addprefix $(OBJ_DIR)/,$(RAW_OBJS))
LIB			=	libft/libft.a
INCLUDES	:=	-I . -I libft/includes
FLAGS		=	-Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	make -C libft
	gcc $(OBJS) $(LIB) $(INCLUDES) $(FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(INCLUDES) $(FLAGS) -o $@ -c $<

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

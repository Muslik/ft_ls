# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/10 17:38:22 by dmorgil           #+#    #+#              #
#    Updated: 2018/12/21 22:08:25 by dmorgil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   ft_ls
HEADER      =   includes/ft_ls.h
SRC_DIR     =   ./sources
OBJ_DIR     =   ./objects
RAW_SRC     =	main.c \
				ft_vector_create.c ft_vector_to_array.c ft_vector_push_back.c \
				ft_vector_free.c ft_ceill.c ft_floorl.c \
				ft_vector_get_functions.c ft_merge_sort_ft_ls.c\
				ft_parse.c ft_detailed_list.c ft_display_file.c \
				ft_print_term.c

RAW_OBJS=$(RAW_SRC:.c=.o)
SRCS=$(addprefix $(SRC_DIR)/,$(RAW_SRC))
OBJS=$(addprefix $(OBJ_DIR)/,$(RAW_OBJS))
OBJS_CLEAN  = $(strip $(foreach f,$(OBJS),$(wildcard $(f))))
NAME_CLEAN  = $(strip $(foreach f,$(NAME),$(wildcard $(f))))
LIB			=	libft/libft.a
INCLUDES	:=	-I includes -I libft/includes
FLAGS		=	-Wall -Wextra -Werror -o3 -ofast

RED			=	\033[0;31m
GREEN		=	\033[0;32m
NC			=	\033[0m

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo "$(GREEN)compiling executable...$(NC)"
	@make -C libft
	@gcc $(OBJS) $(LIB) $(INCLUDES) $(FLAGS) -o $(NAME)
	@echo "$(GREEN)./ft_ls is ready to test$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@gcc $(INCLUDES) $(FLAGS) -o $@ -c $<

clean:
ifneq ($(OBJS_CLEAN),)
	@make clean -C libft
	@rm -rf $(OBJS)
	@echo "\033[31mft_ls Objects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"
else
	@echo "\033[34m\033[1mObjects already cleaned\033[0m"
endif

fclean: clean
ifneq ($(NAME_CLEAN),)
	@make fclean -C libft
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"
else
	@echo "\033[34m\033[1mObjects and bin already cleaned\033[0m"
endif

test:
	gcc test.c

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmorgil  <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/03 16:20:46 by dmorgil           #+#    #+#              #
#    Updated: 2018/12/17 15:13:47 by dmorgil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME=libft.a
CC=gcc
SRC_DIR=./srcs
OBJ_DIR=./objs
RAW_SRC=ft_memchr.c ft_memccpy.c ft_memmove.c ft_memcpy.c \
	 ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	 ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	 ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
	 ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	 ft_memset.c ft_bzero.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c \
	 ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	 ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	 ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
	 ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
	 ft_isblank.c ft_islower.c ft_isspace.c ft_isupper.c ft_isxdigit.c \
	 ft_isgraph.c ft_strisnumeric.c ft_strislowercase.c ft_strisalpha.c \
	 ft_iscntrl.c ft_strisprintable.c ft_strlowcase.c ft_strupcase.c
RAW_OBJS=$(RAW_SRC:.c=.o)
SRCS=$(addprefix $(SRC_DIR)/,$(RAW_SRC))
OBJS=$(addprefix $(OBJ_DIR)/,$(RAW_OBJS))
OBJS_CLEAN = $(strip $(foreach f,$(OBJS),$(wildcard $(f))))
NAME_CLEAN = $(strip $(foreach f,$(NAME),$(wildcard $(f))))
INCLUDES= -I includes
FLAGS=-Wall -Wextra -Werror

.PHONY: all clean fclean re

RED			=	\033[0;31m
GREEN		=	\033[0;32m
NC			=	\033[0m

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
ifneq ($(OBJS_CLEAN),)
	@rm -rf $(OBJS)
	@echo "\033[31mLibft Objects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"
else
endif

fclean: clean
ifneq ($(NAME_CLEAN),)
	@rm -rf $(NAME)
	@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"
else
endif

re: fclean all

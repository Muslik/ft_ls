# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmorgil  <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/03 16:20:46 by dmorgil           #+#    #+#              #
#    Updated: 2018/12/25 22:30:29 by dmorgil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME=libft.a
CC=gcc
SRC_DIR=./srcs
OBJ_DIR=./objs
RAW_SRC=ft_memchr.c ft_memccpy.c ft_memmove.c ft_memcpy.c \
	 ft_memcmp.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	 ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	 ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
	 ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	 ft_bzero.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c \
	 ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	 ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	 ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
	 ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
	 ft_isblank.c ft_islower.c ft_isspace.c ft_isupper.c ft_isxdigit.c \
	 ft_isgraph.c ft_strisnumeric.c ft_strislowercase.c ft_strisalpha.c \
	 ft_iscntrl.c ft_strisprintable.c ft_strlowcase.c ft_strupcase.c \
	 ft_itoa_base.c ft_strlen.c ft_memset.c\
# RAW_OBJS=$(RAW_SRC:.c=.o)
RAW_OBJS=ft_memchr.o ft_memccpy.o ft_memmove.o ft_memcpy.o \
	 ft_memcmp.o ft_strlen.o ft_strdup.o ft_strcpy.o ft_strncpy.o ft_strcat.o \
	 ft_strncat.o ft_strlcat.o ft_strchr.o ft_strrchr.o ft_strstr.o \
	 ft_strnstr.o ft_strcmp.o ft_strncmp.o ft_atoi.o ft_isalpha.o ft_isdigit.o \
	 ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o \
	 ft_bzero.o ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o \
	 ft_strclr.o ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o \
	 ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o \
	 ft_strsplit.o ft_itoa.o ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o \
	 ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_lstnew.o \
	 ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o \
	 ft_isblank.o ft_islower.o ft_isspace.o ft_isupper.o ft_isxdigit.o \
	 ft_isgraph.o ft_strisnumeric.o ft_strislowercase.o ft_strisalpha.o \
	 ft_iscntrl.o ft_strisprintable.o ft_strlowcase.o ft_strupcase.o ft_memset.o\
	 ft_itoa_base.o\

SRCS=$(addprefix $(SRC_DIR)/,$(RAW_SRC))
OBJS=$(addprefix $(OBJ_DIR)/,$(RAW_OBJS))
OBJS_CLEAN = $(strip $(foreach f,$(OBJS),$(wildcard $(f))))
NAME_CLEAN = $(strip $(foreach f,$(NAME),$(wildcard $(f))))
INCLUDES= -I includes
FLAGS=-Wall -Wextra -Werror -O3 -Ofast

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

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER)
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

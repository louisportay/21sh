# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 17:01:50 by lportay           #+#    #+#              #
#    Updated: 2018/02/08 16:21:50 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re

CC= gcc-7
CFLAGS= -Wall -Wextra -Werror
DEBUG=sanitize
ARCH:= $(shell uname)

OBJ_D:=obj

ifeq ($(ARCH), Darwin)
	CC= clang
endif

ifeq ($(DEBUG),yes)
	CFLAGS+= -g3
else ifeq ($(DEBUG),sanitize)
	CFLAGS+= -fsanitize=address -g3
endif

include ft_string/string.mk
include ft_astr/astr.mk
include ft_hashset/hashset.mk
include ft_ctype/ctype.mk
include ft_stdio/stdio.mk
include qbuf/qbuf.mk
include stack/stack.mk
include ft_list/list.mk
include dlst/dlst.mk

OBJ:=$(addprefix $(OBJ_D)/, $(ITEMS))

vpath %.c $(SRC_D)
vpath %.h $(SRC_D)

NAME= libft.a

INCLUDE:=-Iinc

GREEN="\033[32m"
RESET="\033[0m"

all: $(NAME)

$(NAME): $(OBJ)
		ar rc $@ $?
		ranlib $@
		@echo $(GREEN)$(NAME)" Successfully created"$(RESET)


$(OBJ_D)/%.o: %.c #$(HEADERS)
	@mkdir -p $(OBJ_D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	-$(RM) -r $(OBJ_D)

fclean: clean
	-$(RM) $(NAME)

re: fclean all

debug:
	@echo $(SRC_D)
	@echo $(OBJ)
	@echo $(HEADERS)

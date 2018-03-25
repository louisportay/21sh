# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 17:01:50 by lportay           #+#    #+#              #
#    Updated: 2018/03/25 20:57:43 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re

CC= gcc-8
CFLAGS= -Wall -Wextra -Werror $(INCLUDE)
DEBUG=yes#sanitize
ARCH:= $(shell uname)

ifeq ($(ARCH), Darwin)
	CC= clang
endif


ifeq ($(DEBUG),yes)
	CFLAGS+= -g3
else ifeq ($(DEBUG),sanitize)
	CFLAGS+= -fsanitize=address -g3
endif

NAME= libft.a
all: $(NAME)

OBJDIR=obj
include ft_string/string.mk
include ft_astr/astr.mk
include ft_hashset/hashset.mk
include ft_ctype/ctype.mk
include ft_stdio/stdio.mk
include qbuf/qbuf.mk
include stack/stack.mk
include ft_list/list.mk
include ft_dlst/dlst.mk
#include ft_printf/ft_printf.mk

vpath %.c $(SRCDIR)
vpath %.h $(SRCDIR)


GREEN="\033[32m"
RESET="\033[0m"


$(NAME): $(OBJ)
		ar rc $@ $?
		ranlib $@
		@echo $(GREEN)$(NAME)" Successfully created"$(RESET)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

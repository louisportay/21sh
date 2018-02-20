# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 17:01:50 by lportay           #+#    #+#              #
#    Updated: 2018/02/11 16:42:17 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re

CC= gcc-7
CFLAGS= -Wall -Wextra -Werror $(INCLUDE)
DEBUG=sanitize
ARCH:= $(shell uname)

ifeq ($(ARCH), Darwin)
	CC= clang
endif
ifeq ($(ARCH), Linux)
	CC=gcc
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

vpath %.c $(SRCDIR)
vpath %.h $(SRCDIR)


GREEN="\033[32m"
RESET="\033[0m"

debug: 
	@echo $(ARCH)
$(NAME): $(OBJ)
		ar rc $@ $?
		ranlib $@
		@echo $(GREEN)$(NAME)" Successfully created"$(RESET)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

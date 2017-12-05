# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 17:01:50 by lportay           #+#    #+#              #
#    Updated: 2017/11/30 17:32:40 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re

CC= gcc-7
CFLAGS= -Wall -Wextra -Werror -I $(INCLUDE)
DEBUG=no
ARCH:= $(shell uname)

ifeq ($(ARCH), Darwin)
	CC= clang
endif
ifeq ($(DEBUG),yes)
	CFLAGS+= -g
else ifeq ($(DEBUG),sanitize)
	CFLAGS+= -fsanitize=address
endif

include libfiles.mk

NAME= libft.a

GREEN="\033[32m"
RESET="\033[0m"

all: $(NAME)

$(NAME): $(LIBOBJS)
		ar rc $@ $?
		ranlib $@
		@echo $(GREEN)$(NAME)" Successfully created"$(RESET)

include librules.mk

clean:
	-rm -rf $(LIBOBJDIR)

fclean: clean
	-rm $(NAME)

re: fclean all

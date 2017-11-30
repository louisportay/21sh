# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 17:01:50 by lportay           #+#    #+#              #
#    Updated: 2017/11/30 08:53:35 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re

include libfiles.mk

CC= gcc-7
CFLAGS= -Wall -Wextra -Werror -I $(INCLUDE)
DEBUG=no

ifeq ($(DEBUG),yes)
	CFLAGS+= -g
else ifeq ($(DEBUG),sanitize)
	CFLAGS+= -fsanitize=address
endif

NAME= libft.a

GREEN="\033[32m"
RESET="\033[0m"

all: $(NAME)

include librules.mk

clean:
	-rm -rf $(LIBOBJDIR)

fclean: clean
	-rm $(NAME)

re: fclean all

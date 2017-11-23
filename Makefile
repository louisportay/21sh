# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/13 10:52:14 by lportay           #+#    #+#              #
#    Updated: 2017/11/23 13:41:24 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re
vpath %.c srcs/
export $(DEBUG)

CC= gcc-7 
DEBUG=sanitize
OPT=LIB
ARCH= $(shell uname)

ifeq ($(DEBUG), yes)
	CFLAGS= -Wall -Wextra -Werror -g -I $(INCLUDE) -I $(LIBDIR)$(INCLUDE)
else ifeq ($(DEBUG), sanitize)
	CFLAGS= -Wall -Wextra -Werror -g -fsanitize=address -I $(INCLUDE) -I $(LIBDIR)$(INCLUDE)
else
	CFLAGS= -Wall -Wextra -Werror -I $(INCLUDE) -I $(LIBDIR)$(INCLUDE)
endif

INCLUDE= includes/
vpath %.h $(INCLUDE)
HEADERS= ft_21sh.h

SRCS=	main.c\
	ft_21sh.c\
	line.c\
	error.c\
	signal.c\
	lexer.c\
	tools.c\
	prompt.c\

OBJ= $(SRCS:%.c=%.o)
OBJDIR= obj

LIB= libft.a
LIBDIR= libft/

NAME=21sh

GREEN="\033[32m"
RESET="\033[0m"

all: $(LIB) $(NAME)

$(NAME): $(addprefix $(OBJDIR)/, $(OBJ)) $(LIBDIR)$(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(addprefix $(OBJDIR)/, $(OBJ)) -L$(LIBDIR) -lft -ltermcap
	@echo $(GREEN)$(NAME)" Successfully created"$(RESET)

$(OBJDIR)/%.o: %.c $(HEADERS) | $(OBJDIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR):
	-mkdir -p $@

$(LIB): 
	@$(MAKE) -C $(LIBDIR)

main: $(LIB)
	$(CC) $(CFLAGS) -o test $(main) -L$(LIBDIR) -lft -ltermcap
	-rm -f $(main:.c=.o)

clean:

ifeq ($(OPT), LIB)
	$(MAKE) clean -C $(LIBDIR)
else

endif
	-rm -rf $(OBJDIR) 
	@-rm -f a.out
	@-rm -f test
	@-rm -rf test.dSYM

fclean: clean

ifeq ($(OPT), LIB)
	$(MAKE) fclean -C $(LIBDIR)
else

endif		
	-rm -f $(NAME)
	@-rm -rf $(NAME).dSYM

re : fclean all

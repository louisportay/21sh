# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/13 10:52:14 by lportay           #+#    #+#              #
#    Updated: 2017/11/30 17:32:26 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all
vpath %.c srcs/
vpath %.h includes/

CC= gcc-7 
CFLAGS= -Wall -Wextra -Werror -I $(INCLUDE) -I $(LIBDIR)$(INCLUDE)
DEBUG=sanitize
OPT=LIB
ARCH:= $(shell uname)

ifeq ($(ARCH), Darwin)
	CC= clang
endif
ifeq ($(DEBUG), yes)
	CFLAGS+= -g
else ifeq ($(DEBUG), sanitize)
	CFLAGS+= -fsanitize=address
endif

INCLUDE= includes/
HEADERS= ft_21sh.h

SRCS=	main.c\
		ft_21sh.c\
		line.c\
		error.c\
		signal.c\
		lexer.c\
		tools.c\
		prompt.c\
		history.c\

#OBJ= $(SRCS:%.c=%.o)
OBJDIR= obj
OBJ= $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))

LIB= libft.a
LIBDIR= libft/

NAME= 21sh

GREEN="\033[32m"
RESET="\033[0m"

all: $(LIB) $(NAME)

$(NAME): $(LIBDIR)$(LIB) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(LIBDIR) -lft -ltermcap
	@echo $(GREEN)$(NAME)" Successfully created"$(RESET)

$(OBJDIR)/%.o: %.c $(HEADERS) | $(OBJDIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR):
	-mkdir -p $@

$(LIB):
	@$(MAKE) -C $(LIBDIR)

$(LIBDIR)$(LIB):
	@$(MAKE) -C $(LIBDIR)

main: $(LIB)
	$(CC) $(CFLAGS) -o test $(main) -L$(LIBDIR) -lft -ltermcap
	-rm -f $(main:.c=.o)

clean:

ifeq ($(OPT), LIB)
	@$(MAKE) clean -C $(LIBDIR)
endif
	-rm -rf $(OBJDIR) 
	@-rm -f a.out
	@-rm -f test
	@-rm -rf test.dSYM

fclean: clean

ifeq ($(OPT), LIB)
	@$(MAKE) fclean -C $(LIBDIR)
endif		
	-rm -f $(NAME)
	@-rm -rf $(NAME).dSYM

re : fclean all

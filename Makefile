# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/13 10:52:14 by lportay           #+#    #+#              #
#    Updated: 2017/11/28 17:18:12 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all main
vpath %.c srcs/ libft/

include libft/libfiles.mk

CC= gcc-7 
DEBUG=sanitize
OPT=LIB
ARCH= $(shell uname)
CFLAGS= -Wall -Wextra -Werror -I $(INCLUDE) -I $(LIBDIR)$(INCLUDE)

ifeq ($(DEBUG), yes)
	CFLAGS+= -g
else ifeq ($(DEBUG), sanitize)
	CFLAGS+= -fsanitize=address
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
	history.c\

OBJ= $(SRCS:%.c=%.o)
OBJDIR= obj

LIB= libft.a
LIBDIR= libft/

NAME= 21sh

GREEN="\033[32m"
RESET="\033[0m"

all: $(LIB) $(NAME)
#ameliorer le linking avec la librairie, eviter d'ouvrir le dossier avec la directive includes

$(NAME): $(addprefix $(OBJDIR)/, $(OBJ)) $(LIBDIR)$(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(addprefix $(OBJDIR)/, $(OBJ)) -L$(LIBDIR) -lft -ltermcap
	@echo $(GREEN)$(NAME)" Successfully created"$(RESET)

$(OBJDIR)/%.o: %.c $(HEADERS) | $(OBJDIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR):
	-mkdir -p $@

$(LIBDIR)$(LIB):
	$(MAKE) -C $(LIBDIR)

$(LIB):
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

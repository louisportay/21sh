# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/13 10:52:14 by lportay           #+#    #+#              #
#    Updated: 2018/02/08 20:13:33 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all

SRCDIR= srcs/ \
		srcs/line \

vpath %.c $(SRCDIR)
vpath %.h includes/

CC= gcc-7 
CFLAGS= -Wall -Wextra -Werror $(INCLUDE)#-I $(INCLUDE) -I $(LIBDIR)$(INCLUDE)
DEBUG=sanitize
OPT=LIB
ARCH:= $(shell uname)

ifeq ($(ARCH), Darwin)
	CC= clang
endif

ifeq ($(DEBUG), yes)
	CFLAGS+= -g3
else ifeq ($(DEBUG), sanitize)
	CFLAGS+= -g3 -fsanitize=address
endif

INCLUDE=\
-Iincludes\
-I$(LIBDIR)/inc
HEADERS= ft_21sh.h\
		 history.c\
		 line.h\
		 prompt.h\
		 token.h

SRCS=	main.c\
		ft_21sh.c\
		error.c\
		signal.c\
		tools.c\
		prompt.c\
		history.c\
		rawline.c\
		quote.c\
		\
		line.c\
		lineread.c\
		move_cursor.c\
		print_line.c\
		up_down_keys.c\
		go_to.c\
		del_insert.c\
		kill_yank.c\
		line_utils.c\
		clear.c\
		line_test.c\
		\
		lexer.c\
		filter_tokens.c\

OBJDIR= obj
OBJ= $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))

LIBDIR= lib21sh/
LIB= libft.a

NAME= 21sh

GREEN="\033[32m"
RESET="\033[0m"

all: $(LIB) $(NAME)

$(NAME): $(LIBDIR)$(LIB) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(LIBDIR) -lft -ltermcap
	@echo $(GREEN)$(NAME)" Successfully created"$(RESET)

$(OBJDIR)/%.o: %.c $(HEADERS) | $(OBJDIR)
	$(COMPILE.c) $< -o $@ $(INCLUDE)

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

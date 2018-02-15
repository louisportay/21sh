# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/13 10:52:14 by lportay           #+#    #+#              #
#    Updated: 2018/02/15 19:49:43 by vbastion         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all

SRCDIR= srcs/ \
		srcs/line \
		srcs/parser \
		srcs/exec \
		srcs/builtins \

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
-I$(LIBDIR)stack\
-I$(LIBDIR)qbuf\
-I$(LIBDIR)ft_stdio\
-I$(LIBDIR)ft_string\
-I$(LIBDIR)ft_astr\
-I$(LIBDIR)ft_ctype\
-I$(LIBDIR)ft_hashset\
-I$(LIBDIR)ft_list\
-I$(LIBDIR)ft_dlst\
-I$(LIBDIR)kvp

HEADERS= ft_21sh.h\
		 history.c\
		 line.h\
		 prompt.h\
		 token.h

SRCS=	main.c\
		ft_21sh.c\
		initvar.c\
		initshell.c\
		error.c\
		signal.c\
		tools.c\
		utils.c\
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
		redir.c\
		parser.c\
		printers.c\
		asmt.c\
		bridge_token.c\
		bridge_dlist.c\
		bridge_astr.c\
		proc_next.c\
		ptok_lifecycle.c\
		clearers.c\
		exec.c\
		job_exec.c\
		proc_exec.c\
		get_path.c\
		job_utils.c\
		job_wait.c\
		proc_chgstat.c\
		job_lifecycle.c\
		bridge_exec_astr.c\
		exec_assignments.c\
		\
		builtin_echo.c\
		builtin_printenv.c\
		builtin_hash.c\

OBJDIR= obj
#include srcs/parser/parser.mk
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

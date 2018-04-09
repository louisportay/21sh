# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/13 10:52:14 by lportay           #+#    #+#              #
#    Updated: 2018/04/09 22:19:27 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all

SRCDIR= srcs/ \
		srcs/bridge \
		srcs/utils \
		srcs/init \
		srcs/line \
		srcs/history \
		srcs/lexer \
		srcs/parser \
		srcs/exec \
		srcs/builtins \
		srcs/expand \
		srcs/expand/path_matching \
		srcs/expand/braces \
		srcs/expand/tilde \
		srcs/expand/quotes \
		srcs/expand/param \

vpath %.c $(SRCDIR)
vpath %.h includes/

CC= gcc-8
CFLAGS= -Wall -Wextra -Werror $(INCLUDE)
DEBUG=sanitize
OPT=LIB
ARCH:= $(shell uname)
TERMLIB=-ltermcap

ifeq ($(ARCH), Darwin)
	CC= clang
endif
ifeq ($(ARCH), Linux)
	CC=gcc-8
	TERMLIB=-lcurses
	CFLAGS+=-D _GNU_SOURCE
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
-I$(LIBDIR)kvp\
-I$(LIBDIR)ft_printf\

HEADERS=\
ft_21sh.h\
history.h\
line.h\
prompt.h\
token.h\
builtins.h\
dir_explorer.h\
exec.h\
expand.h\
expand_braces.h\
expand_param.h\
expand_quotes.h\
expand_tilde.h\
ft_21sh.h\
history.h\
job_control.h\
line.h\
parser.h\
pattern_matching.h\
posix_classes.h\
prompt.h\
token.h\

SRCS=	main.c\
		ft_21sh.c\
		initvar.c\
		initshell.c\
		init_ctx.c\
		getopt.c\
		error.c\
		signal.c\
		tools.c\
		utils.c\
		\
		rawline.c\
		default.c\
		prompt.c\
		prompt_utils.c\
		prompt_flags1.c\
		prompt_flags2.c\
		line.c\
		user_input.c\
		lineread.c\
		move_cursor.c\
		print_line.c\
		arrow_keys.c\
		go_to.c\
		go_line.c\
		del_insert.c\
		kill_yank.c\
		line_utils.c\
		clear.c\
		get_state.c\
		quote.c\
		paren.c\
		test_arrow.c\
		test_kill_yank.c\
		test_go_line.c\
		test_go_to.c\
		test_other.c\
		\
		history.c\
		manage_history.c\
		history_utils.c\
		\
		lexer.c\
		tokrules.c\
		filter_tokens.c\
		str_from_token.c\
		token_utils.c\
		clear_token.c\
		is.c\
		handle_tok.c\
		\
		redir.c\
		redir_and.c\
		redir_err.c\
		parser.c\
		printers.c\
		asmt.c\
		bridge_token.c\
		bridge_dlist.c\
		\
		bridge_astr.c\
		bridge_list.c\
		proc_next.c\
		proc_func.c\
		ptok_lifecycle.c\
		clearers.c\
		exec.c\
		job_exec.c\
		job_exec_loop.c\
		job_pipe.c\
		job_one.c\
		proc_exec.c\
		exec_pipe.c\
		get_path.c\
		path_fromcache.c\
		job_lifecycle.c\
		exec_assignments.c\
		prepare_fork.c\
		blt_output.c\
		get_command.c\
		\
		builtin_cd.c\
		builtin_cd_utils.c\
		builtin_echo.c\
		builtin_printenv.c\
		builtin_hash.c\
		builtin_hash_args.c\
		builtin_hash_args2.c\
		builtin_hash_print.c\
		builtin_set.c\
		builtin_set_args.c\
		builtin_set_args2.c\
		builtin_setenv.c\
		builtin_addenv.c\
		builtin_env_utils.c\
		builtin_unsetenv.c\
		builtin_env.c\
		builtin_envopt.c\
		builtin_history.c\
		builtin_exit.c\
		\
		expand_exec.c\
		expand.c\
		bridge_splitws.c\
		\
		expand_braces.c\
		btok_scan.c\
		btok_lifecycle.c\
		btok_get.c\
		btok_from.c\
		btok_sanitize.c\
		expand_glob.c\
		dir_expand_glob.c\
		dir_explore.c\
		ent_handling.c\
		ent_sort.c\
		ent_match.c\
		pattern_matching_assert.c\
		pattern_matching.c\
		mtok_clear.c\
		mtok_splitstr.c\
		mtok_untilstr.c\
		pattern_matching_tokens.c\
		ttok_lifecycle.c\
		ttok_comb.c\
		ttok_combine.c\
		ttok_compose.c\
		ttok_get.c\
		ttok_utils.c\
		ttok_str.c\
		dir_handle_matched.c\
		pattern_matching_pointers.c\
		ft_utils.c\
		pattern_matching_brackets.c\
		pattern_matching_ematcher.c\
		\
		expand_tilde.c\
		\
		expand_quotes.c\
		\
		expand_param.c\
		scan_dollar.c\
		vtok_dollarpid.c\
		vtok_lifecycle.c\
		vtok_get.c\
		vtok_handletokens.c\
		vtok_sanitize.c\
		vtok_sanitize_utils.c\
		vtok_util.c\
		vtok_str.c\
		vtok_dollar.c\
		vtok_addvar.c\
		vtok_dollarbrace.c\
		vtok_dollarexec.c\
		\
		mtok_print.c\
		mtok_sort.c\
		\
		path_reset.c\
		\
		exec_pipe_error.c\
		vtok_print.c\

OBJDIR= obj
OBJ= $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))

LIBDIR= libft/
LIB= libft.a

NAME= 21sh

GREEN="\033[32m"
RESET="\033[0m"

#.SILENT:

all: $(LIB) $(NAME)

$(NAME): $(LIBDIR)$(LIB) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(LIBDIR) -lft $(TERMLIB)
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
	$(CC) $(CFLAGS) -o test $(main) -L$(LIBDIR) -lft $(TERMLIB)
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

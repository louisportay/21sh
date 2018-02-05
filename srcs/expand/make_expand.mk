# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make_expand.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 17:21:37 by vbastion          #+#    #+#              #
#    Updated: 2018/01/14 17:21:23 by vbastion         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=expand
MAIN:=main_expand.c
CC=gcc
CFLAGS=-Wall -Wextra -Werror
ifeq ($(SANE),true)
CFLAGS+=-fsanitize=address -g3
endif
ifeq ($(SANE),g3)
CFLAGS+=-g3
endif

OBJ_D:=obj
LIB_D:=../../..

MKDIR:=mkdir -p
RM:=/bin/rm -f

vpath %.c braces param path_matching tilde quotes

ITEM:=\
expand.o\
btok_from.o\
btok_get.o\
btok_lifecycle.o\
btok_print.o\
btok_sanitize.o\
btok_scan.o\
expand_braces.o\
ttok_comb.o\
ttok_combine.o\
ttok_compose.o\
ttok_get.o\
ttok_lifecycle.o\
ttok_str.o\
ttok_utils.o\
expand_param.o\
scan_dollar.o\
vtok_addvar.o\
vtok_dollar.o\
vtok_dollarbrace.o\
vtok_dollarexec.o\
vtok_dollarpid.o\
vtok_get.o\
vtok_handletokens.o\
vtok_lifecycle.o\
vtok_print.o\
vtok_sanitize.o\
vtok_sanitize_utils.o\
vtok_str.o\
vtok_util.o\
dir_explore.o\
dir_handle_matched.o\
ent_handling.o\
ent_match.o\
ent_sort.o\
expand_glob.o\
ft_utils.o\
mtok_clear.o\
mtok_print.o\
mtok_splitstr.o\
mtok_untilstr.o\
pattern_matching.o\
pattern_matching_assert.o\
pattern_matching_brackets.o\
pattern_matching_ematcher.o\
pattern_matching_match.o\
pattern_matching_pointers.o\
pattern_matching_tokens.o\
expand_tilde.o\
bridge_splitws.o\
dir_expand_glob.o\
expand_quotes.o
OBJ:=$(addprefix $(OBJ_D)/,$(ITEM))

INCLUDES:=\
-I.\
-Ibraces\
-Itilde\
-Iparam\
-Ipath_matching\
-Iquotes\
-I../../inc\
-I$(LIB_D)/ft_mem/inc\
-I$(LIB_D)/ft_string/inc\
-I$(LIB_D)/ft_membuf/inc\
-I$(LIB_D)/qbuf/inc\
-I$(LIB_D)/ft_list/inc\
-I$(LIB_D)/ft_astr/inc\
-I$(LIB_D)/ft_delegates/inc

LIBRARIES:=\
$(LIB_D)/ft_mem/libftmem.a\
$(LIB_D)/ft_string/libftstring.a\
$(LIB_D)/ft_membuf/libftmembuf.a\
$(LIB_D)/qbuf/libqbuf.a\
$(LIB_D)/ft_list/libftlist.a\
$(LIB_D)/ft_astr/libftastr.a

HEADER:=\
	expand.h

LNKS:=\
../kvp/kvp_copy.c\
../kvp/kvp_get.c

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(MAIN) -o $(NAME) $(OBJ) $(INCLUDES) $(LIBRARIES) $(LNKS)

$(OBJ_D)/%.o: %.c $(HEADER)
	@$(MKDIR) $(OBJ_D)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	$(RM) -r $(OBJ_D)

fclean: clean
	$(RM) $(NAME)
	@$(RM) -r $(NAME).dSYM

re: fclean all

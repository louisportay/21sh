# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lportay <lportay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 17:01:50 by lportay           #+#    #+#              #
#    Updated: 2017/11/23 11:44:39 by lportay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re

CC= gcc-7

DEBUG=no

ifeq ($(DEBUG),yes)
	CFLAGS= -Wall -Wextra -Werror -g -I $(INCLUDE)
else ifeq ($(DEBUG),sanitize)
	CFLAGS= -Wall -Wextra -Werror -fsanitize=address -I $(INCLUDE)
else
	CFLAGS= -Wall -Wextra -Werror -I $(INCLUDE)
endif

INCLUDE= includes/

NAME= libft.a

#vpath %.c ft_string/ ft_stdio/ ft_stdlib/ lst/ dlst/ buffer/ ft_ctype/ ft_wchar/ other/ ft_printf/ ft_hash
vpath %.h $(INCLUDE)

#HEADERS= buffer.h\
	dlst.h\
	ft_ctype.h\
	ft_stdio.h\
	ft_stdlib.h\
	ft_string.h\
	libft.h\
	lst.h\
	other.h\
	ft_printf.h\
	ft_hash.h\

HEADER= libft.h

CTYPE=	ft_isprint.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isunicode.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_isspace.c

STRING=	ft_bzero.c\
	ft_memcpy.c\
	ft_memdel.c\
	ft_strlen.c\
	ft_stroccur.c\
	ft_strcpy.c\
	ft_strncpy.c\
	ft_strsplit.c\
	ft_strdup.c\
	ft_strchr.c\
	ft_strdel.c\
	ft_strjoin.c\
	ft_strjoin_dup.c\
	ft_strnew.c\
	ft_strrev.c\
	ft_strlower.c\
	ft_strupper.c\
	ft_strcmp.c\
	ft_strncmp.c\
	ft_strmatch.c\
	ft_strrep.c\
	ft_strstr.c\
	ft_strstri.c\
	ft_strsplitquote.c\
	ft_strexpand.c\
	ft_strcat.c\
	ft_basename.c\
	ft_dirname.c\
	fullpath.c\

STDLIB=	ft_bwidth.c\
	ft_itoa.c\
	ft_itoa_base.c\
	ft_itoa_base_u.c\
	ft_atoi.c\
	ft_atoi_base.c\
	ft_swap.c\
	ft_fswap.c\
	ft_cswap.c\
	ft_lwidth.c\
	ft_abs.c\
	ft_darray.c\
	ft_getenv.c\
	ft_setenv.c\
	ft_unsetenv.c\
	ft_copyenv.c\

STDIO=	get_next_line.c\
	ft_putchar.c\
	ft_putchar_fd.c\
	ft_putnchar.c\
	ft_putnchar_fd.c\
	ft_putstr.c\
	ft_putstr_fd.c\
	ft_putnbr.c\
	ft_putendl.c\
	ft_getchar.c

LST=	ft_lstadd.c\
	ft_lstaddend.c\
	ft_lstaddr.c\
	ft_lstprint.c\
	ft_lstdel.c\
	ft_lstdelone.c\
	ft_lstnew.c\
	ft_lstcount.c\
	ft_lstindex.c\
	ft_lstremove.c\
	ft_lstmove.c\
	ft_lstinsert.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_tabtolst.c\
	ft_lstnewaddr.c

DLST=   ft_dlstadd.c\
	ft_dlstaddend.c\
	ft_dlstprint.c\
	ft_dlstdel.c\
	ft_dlstdelone.c\
	ft_dlstnew.c\
	ft_dlstnewaddr.c\
	ft_dlstcount.c\
	ft_dlstindex.c\
	ft_dlstremove.c\
	ft_dlstaddr.c\
	ft_dlsthead.c\
	ft_dlstend.c\
	ft_dlstinsert.c\
	str_to_dlst.c\

BUFFER= putc_in_buf.c\
	putc_in_buf_fd.c\
	putnbr_in_buf.c\
	putnc_in_buf.c\
	putns_in_buf.c\
	putnws_in_buf.c\
	puts_in_buf.c\
	putwc_in_buf.c\
	putws_in_buf.c

WCHAR= 	ft_wcslen.c\
	ft_wcstrdel.c\
	ft_wcsdup.c

OTHER=	fill_array.c\
	fill_darray.c\
	del_array.c\
	delvoid.c\

PRINTF= ft_printf.c\
	 parsing.c\
	 flags.c\
	 tools.c\
	 cast.c\
	 is.c\
	 hex_oct.c\
	 int_unsigned.c\
	 char_str.c\
	 print_input.c

HASH=	hashindex.c\
	hashdel.c\
	hashinsert.c\
	hashlookup.c\
	hashcreate.c\
	hashclear.c\
	hashinit.c\

BTREE=	btree_apply.c\
	btree_create_node.c\
	btree_insert_data.c\
	btree_search_item.c\
	print_btree.c\

OBJDIR= obj

PRINTFOBJ= $(PRINTF:%.c=%.o)
PRINTFOBJDIR= $(OBJDIR)/ft_printf

CTYPEOBJ= $(CTYPE:%.c=%.o)
CTYPEOBJDIR= $(OBJDIR)/ft_ctype

STDIOOBJ= $(STDIO:%.c=%.o)
STDIOOBJDIR= $(OBJDIR)/ft_stdio

STDLIBOBJ= $(STDLIB:%.c=%.o)
STDLIBOBJDIR= $(OBJDIR)/ft_stdlib

STRINGOBJ= $(STRING:%.c=%.o)
STRINGOBJDIR= $(OBJDIR)/ft_string

LSTOBJ= $(LST:%.c=%.o)
LSTOBJDIR= $(OBJDIR)/lst

DLSTOBJ= $(DLST:%.c=%.o)
DLSTOBJDIR= $(OBJDIR)/dlst

WCHAROBJ= $(WCHAR:%.c=%.o)
WCHAROBJDIR= $(OBJDIR)/ft_wchar

BUFFEROBJ= $(BUFFER:%.c=%.o)
BUFFEROBJDIR= $(OBJDIR)/buffer

OTHEROBJ= $(OTHER:%.c=%.o)
OTHEROBJDIR= $(OBJDIR)/other

HASHOBJ= $(HASH:%.c=%.o)
HASHOBJDIR= $(OBJDIR)/ft_hash

BTREEOBJ= $(BTREE:%.c=%.o)
BTREEOBJDIR= $(OBJDIR)/ft_btree

GREEN="\033[32m"
RESET="\033[0m"
all: $(NAME)

$(NAME): $(addprefix $(PRINTFOBJDIR)/, $(PRINTFOBJ)) $(addprefix $(CTYPEOBJDIR)/, $(CTYPEOBJ)) $(addprefix $(STDIOOBJDIR)/, $(STDIOOBJ)) $(addprefix $(STDLIBOBJDIR)/, $(STDLIBOBJ)) $(addprefix $(STRINGOBJDIR)/, $(STRINGOBJ)) $(addprefix $(LSTOBJDIR)/, $(LSTOBJ)) $(addprefix $(DLSTOBJDIR)/, $(DLSTOBJ)) $(addprefix $(WCHAROBJDIR)/, $(WCHAROBJ)) $(addprefix $(BUFFEROBJDIR)/, $(BUFFEROBJ)) $(addprefix $(OTHEROBJDIR)/, $(OTHEROBJ)) $(addprefix $(HASHOBJDIR)/, $(HASHOBJ)) $(addprefix $(BTREEOBJDIR)/, $(BTREEOBJ))
	ar rc $@ $?
	ranlib $@
	@echo $(GREEN)$(NAME)" Successfully created"$(RESET)

$(PRINTFOBJDIR)/%.o: ft_printf/%.c ft_printf.h $(HEADER) | $(PRINTFOBJDIR)
	$(COMPILE.c) $< -o $@

$(BUFFEROBJDIR)/%.o: buffer/%.c buffer.h $(HEADER) | $(BUFFEROBJDIR)
	$(COMPILE.c) $< -o $@

$(DLSTOBJDIR)/%.o: dlst/%.c ft_dlst.h $(HEADER) | $(DLSTOBJDIR)
	$(COMPILE.c) $< -o $@

$(LSTOBJDIR)/%.o: lst/%.c ft_lst.h $(HEADER) | $(LSTOBJDIR)
	$(COMPILE.c) $< -o $@

$(CTYPEOBJDIR)/%.o: ft_ctype/%.c ft_ctype.h $(HEADER) | $(CTYPEOBJDIR)
	$(COMPILE.c) $< -o $@

$(STDIOOBJDIR)/%.o: ft_stdio/%.c ft_stdio.h $(HEADER) | $(STDIOOBJDIR)
	$(COMPILE.c) $< -o $@

$(STDLIBOBJDIR)/%.o: ft_stdlib/%.c ft_stdlib.h $(HEADER) | $(STDLIBOBJDIR)
	$(COMPILE.c) $< -o $@

$(WCHAROBJDIR)/%.o: ft_wchar/%.c ft_wchar.h $(HEADER) | $(WCHAROBJDIR)
	$(COMPILE.c) $< -o $@

$(OTHEROBJDIR)/%.o: other/%.c other.h $(HEADER) | $(OTHEROBJDIR)
	$(COMPILE.c) $< -o $@

$(STRINGOBJDIR)/%.o: ft_string/%.c ft_string.h $(HEADER)| $(STRINGOBJDIR)
	$(COMPILE.c) $< -o $@

$(HASHOBJDIR)/%.o: ft_hash/%.c ft_hash.h $(HEADER)| $(HASHOBJDIR)
	$(COMPILE.c) $< -o $@

$(BTREEOBJDIR)/%.o: ft_btree/%.c ft_btree.h $(HEADER)| $(BTREEOBJDIR)
	$(COMPILE.c) $< -o $@

#$(OBJDIR)/%.o: %.c $(HEADERS) | $(OBJDIR)
#	$(COMPILE.c) $< -o $@

$(OBJDIR):
	-mkdir -p $@
$(CTYPEOBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(STDIOOBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(STDLIBOBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(STRINGOBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(BUFFEROBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(WCHAROBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(LSTOBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(DLSTOBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(OTHEROBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(PRINTFOBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(HASHOBJDIR): | $(OBJDIR)
	-mkdir -p $@
$(BTREEOBJDIR): | $(OBJDIR)
	-mkdir -p $@

clean:
	-rm -rf $(OBJDIR)
	@-rm -f a.out

fclean: clean
	-rm -f $(NAME)

re: fclean all

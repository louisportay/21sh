vpath %.c ft_string/ ft_stdio/ ft_stdlib/ lst/ dlst/ buffer/ ft_ctype/ ft_wchar/ other/ ft_printf/ ft_hash/ ft_btree/ utest/ stack/
vpath %.h includes/

INCLUDE= includes
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
	getpath.c\

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
	abs.c\
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
	dlst_to_str.c\
	ft_dlstdup.c\
	move_dlst_head.c\

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
	hashaddr.c\

BTREE=	btree_apply.c\
	btree_create_node.c\
	btree_insert_data.c\
	btree_search_item.c\
	print_btree.c\

UTEST=	new_test.c\
		del_test.c\
		load_test.c\
		exec_test.c\
		exec_all_tests.c\

STACK=	stack_create.c\
		stack_del.c\
		stack_pop.c\
		stack_print.c\
		stack_push.c\


PRINTFOBJ= $(PRINTF:%.c=%.o)
CTYPEOBJ= $(CTYPE:%.c=%.o)
STDIOOBJ= $(STDIO:%.c=%.o)
STDLIBOBJ= $(STDLIB:%.c=%.o)
STRINGOBJ= $(STRING:%.c=%.o)
LSTOBJ= $(LST:%.c=%.o)
DLSTOBJ= $(DLST:%.c=%.o)
WCHAROBJ= $(WCHAR:%.c=%.o)
BUFFEROBJ= $(BUFFER:%.c=%.o)
OTHEROBJ= $(OTHER:%.c=%.o)
HASHOBJ= $(HASH:%.c=%.o)
BTREEOBJ= $(BTREE:%.c=%.o)
UTESTOBJ= $(UTEST:%.c=%.o)
STACKOBJ= $(STACK:%.c=%.o)

LIBOBJDIR= libobj
PRINTFOBJDIR= $(LIBOBJDIR)/ft_printf
CTYPEOBJDIR= $(LIBOBJDIR)/ft_ctype
STDIOOBJDIR= $(LIBOBJDIR)/ft_stdio
STDLIBOBJDIR= $(LIBOBJDIR)/ft_stdlib
STRINGOBJDIR= $(LIBOBJDIR)/ft_string
LSTOBJDIR= $(LIBOBJDIR)/lst
DLSTOBJDIR= $(LIBOBJDIR)/dlst
WCHAROBJDIR= $(LIBOBJDIR)/ft_wchar
BUFFEROBJDIR= $(LIBOBJDIR)/buffer
OTHEROBJDIR= $(LIBOBJDIR)/other
HASHOBJDIR= $(LIBOBJDIR)/ft_hash
BTREEOBJDIR= $(LIBOBJDIR)/ft_btree
UTESTOBJDIR= $(LIBOBJDIR)/utest
STACKOBJDIR= $(LIBOBJDIR)/stack

LIBOBJS=	$(addprefix $(PRINTFOBJDIR)/, $(PRINTFOBJ))\
			$(addprefix $(CTYPEOBJDIR)/, $(CTYPEOBJ))\
			$(addprefix $(STDIOOBJDIR)/, $(STDIOOBJ))\
			$(addprefix $(STDLIBOBJDIR)/, $(STDLIBOBJ))\
			$(addprefix $(STRINGOBJDIR)/, $(STRINGOBJ))\
			$(addprefix $(LSTOBJDIR)/, $(LSTOBJ))\
			$(addprefix $(DLSTOBJDIR)/, $(DLSTOBJ))\
			$(addprefix $(WCHAROBJDIR)/, $(WCHAROBJ))\
			$(addprefix $(BUFFEROBJDIR)/, $(BUFFEROBJ))\
			$(addprefix $(OTHEROBJDIR)/, $(OTHEROBJ))\
			$(addprefix $(HASHOBJDIR)/, $(HASHOBJ))\
			$(addprefix $(BTREEOBJDIR)/, $(BTREEOBJ))\
			$(addprefix $(UTESTOBJDIR)/, $(UTESTOBJ))\
			$(addprefix $(STACKOBJDIR)/, $(STACKOBJ))\

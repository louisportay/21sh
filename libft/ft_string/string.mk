STRING=\
ft_atoi.c\
ft_basename.c\
ft_dirname.c\
ft_bzero.c\
ft_itoa.c\
ft_ltobuf.c\
ft_memalloc.c\
ft_memcpy.c\
ft_memdel.c\
ft_memdup.c\
ft_strcat.c\
ft_strchr.c\
ft_strcmp.c\
ft_strcpy.c\
ft_strdel.c\
ft_strdup.c\
ft_strindex.c\
ft_strjoin.c\
ft_strlen.c\
ft_strncat.c\
ft_strncmp.c\
ft_strncpy.c\
ft_strnew.c\
ft_stroccur.c\
ft_strsplit.c\
ft_strstr.c\
fullpath.c\
randstring.c\
#__getpath__.c\

STRING_DIR=ft_string

OBJ+=$(addprefix $(OBJDIR)/$(STRING_DIR)/, $(STRING:%.c=%.o))

SRCDIR+=$(STRING_DIR)/

INCLUDE+=-I$(STRING_DIR)/

HEADER=ft_string.h

$(OBJDIR)/$(STRING_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(STRING_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(STRING_DIR):
	mkdir -p $(OBJDIR)/$(STRING_DIR)


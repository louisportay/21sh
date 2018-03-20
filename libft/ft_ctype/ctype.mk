CTYPE=\
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_isnumber.c\
ft_isprint.c\
ft_isspace.c\
ft_isunicode.c\
ft_tolower.c\
ft_toupper.c\
ft_isblank.c\

CTYPE_DIR=ft_ctype

OBJ+=$(addprefix $(OBJDIR)/$(CTYPE_DIR)/, $(CTYPE:%.c=%.o))

SRCDIR+=$(CTYPE_DIR)/

INCLUDE+=-I$(CTYPE_DIR)/

HEADER=ft_ctype.h

$(OBJDIR)/$(CTYPE_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(CTYPE_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(CTYPE_DIR):
	mkdir -p $(OBJDIR)/$(CTYPE_DIR)

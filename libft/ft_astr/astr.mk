ASTR=\
ft_astr_append.c\
ft_astr_beginswith.c\
ft_astr_copy.c\
ft_astr_dup.c\
ft_astr_find.c\
ft_astr_foreach.c\
ft_astr_free.c\
ft_astr_getkey.c\
ft_astr_len.c\
ft_astr_remove_at.c\
ft_astr_rmdup.c\
ft_env_find.c\
ft_astr_replace.c\

ASTR_DIR=ft_astr

OBJ+=$(addprefix $(OBJDIR)/$(ASTR_DIR)/, $(ASTR:%.c=%.o))

SRCDIR+=$(ASTR_DIR)/

INCLUDE+=-I$(ASTR_DIR)/

HEADER=ft_astr.h

$(OBJDIR)/$(ASTR_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(ASTR_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(ASTR_DIR):
	mkdir -p $(OBJDIR)/$(ASTR_DIR)


HASHSET=\
ft_hashset.c\
ft_hashset_free.c\
ft_hash_foreach.c\

HASHSET_DIR=ft_hashset

OBJ+=$(addprefix $(OBJDIR)/$(HASHSET_DIR)/, $(HASHSET:%.c=%.o))

SRCDIR+=$(HASHSET_DIR)/

INCLUDE+=-I$(HASHSET_DIR)/

HEADER=ft_hashset.h

$(OBJDIR)/$(HASHSET_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(HASHSET_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(HASHSET_DIR):
	mkdir -p $(OBJDIR)/$(HASHSET_DIR)


KVP=\

KVP_DIR=kvp

OBJ+=$(addprefix $(OBJDIR)/$(KVP_DIR)/, $(KVP:%.c=%.o))

SRCDIR+=$(KVP_DIR)/

INCLUDE+=-I$(KVP_DIR)/

HEADER=kvp.h

$(OBJDIR)/$(KVP_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(KVP_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(KVP_DIR):
	mkdir -p $(OBJDIR)/$(KVP_DIR)

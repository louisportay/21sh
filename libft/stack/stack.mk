STACK=\
stack_create.c\
stack_del.c\
stack_pop.c\
stack_print.c\
stack_push.c\
stack_dup.c\

STACK_DIR=stack

OBJ+=$(addprefix $(OBJDIR)/$(STACK_DIR)/, $(STACK:%.c=%.o))

SRCDIR+=$(STACK_DIR)/

INCLUDE+=-I$(STACK_DIR)/

HEADER=stack

$(OBJDIR)/$(STACK_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(STACK_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(STACK_DIR):
	mkdir -p $(OBJDIR)/$(STACK_DIR)

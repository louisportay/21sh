LIST=\
ft_list_add.c\
ft_list_count.c\
ft_list_create.c\
ft_list_delete.c\
ft_list_foreach.c\
ft_list_insert.c\
ft_list_last.c\
ft_list_merge.c\
ft_list_next.c\
ft_list_prepend.c\
ft_list_push.c\
ft_list_split.c\

LIST_DIR=ft_list

OBJ+=$(addprefix $(OBJDIR)/$(LIST_DIR)/, $(LIST:%.c=%.o))

SRCDIR+=$(LIST_DIR)/

INCLUDE+=-I$(LIST_DIR)/

HEADER=ft_list.h

$(OBJDIR)/$(LIST_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(LIST_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(LIST_DIR):
	mkdir -p $(OBJDIR)/$(LIST_DIR)

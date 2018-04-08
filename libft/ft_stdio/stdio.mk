STDIO=\
ft_putstr_fd.c\
get_next_line.c\
ft_tmpfile.c\
ft_putnbr.c\

STDIO_DIR=ft_stdio

OBJ+=$(addprefix $(OBJDIR)/$(STDIO_DIR)/, $(STDIO:%.c=%.o))

SRCDIR+=$(STDIO_DIR)/

INCLUDE+=-I$(STDIO_DIR)/

HEADER=ft_stdio.h

$(OBJDIR)/$(STDIO_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(STDIO_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(STDIO_DIR):
	mkdir -p $(OBJDIR)/$(STDIO_DIR)

QBUF=\
qbuf_insert.c\
qbuf_lifecycle.c\

QBUF_DIR=qbuf

OBJ+=$(addprefix $(OBJDIR)/$(QBUF_DIR)/, $(QBUF:%.c=%.o))

SRCDIR+=$(QBUF_DIR)/

INCLUDE+=-I$(QBUF_DIR)/

HEADER=qbuf.h

$(OBJDIR)/$(QBUF_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(QBUF_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(QBUF_DIR):
	mkdir -p $(OBJDIR)/$(QBUF_DIR)

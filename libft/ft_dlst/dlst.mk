DLST=\
delvoid.c\
dlst_from_str.c\
ft_dlstadd.c\
ft_dlstaddend.c\
ft_dlstaddr.c\
ft_dlstcount.c\
ft_dlstdel.c\
ft_dlstdelone.c\
ft_dlstdup.c\
ft_dlstend.c\
ft_dlsthead.c\
ft_dlstindex.c\
ft_dlstinsert.c\
ft_dlstnewaddr.c\
ft_dlstnew.c\
ft_dlstprint.c\
ft_dlstremove.c\
move_dlst_head.c\
str_from_dlst.c\
ft_dlstlast.c\

DLST_DIR=ft_dlst

OBJ+=$(addprefix $(OBJDIR)/$(DLST_DIR)/, $(DLST:%.c=%.o))

SRCDIR+=$(DLST_DIR)/

INCLUDE+=-I$(DLST_DIR)/

HEADER=ft_dlst.h

$(OBJDIR)/$(DLST_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(DLST_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(DLST_DIR):
	mkdir -p $(OBJDIR)/$(DLST_DIR)

$(NAME): $(LIBOBJS)
		ar rc $@ $?
		ranlib $@
		@echo $(GREEN)$(NAME)" Successfully created"$(RESET)

$(PRINTFOBJDIR)/%.o: %.c ft_printf.h $(HEADER) | $(PRINTFOBJDIR)
	$(COMPILE.c) $< -o $@

$(BUFFEROBJDIR)/%.o: %.c buffer.h $(HEADER) | $(BUFFEROBJDIR)
	$(COMPILE.c) $< -o $@

$(DLSTOBJDIR)/%.o: %.c ft_dlst.h $(HEADER) | $(DLSTOBJDIR)
	$(COMPILE.c) $< -o $@

$(LSTOBJDIR)/%.o: %.c ft_lst.h $(HEADER) | $(LSTOBJDIR)
	$(COMPILE.c) $< -o $@

$(CTYPEOBJDIR)/%.o: %.c ft_ctype.h $(HEADER) | $(CTYPEOBJDIR)
	$(COMPILE.c) $< -o $@

$(STDIOOBJDIR)/%.o: %.c ft_stdio.h $(HEADER) | $(STDIOOBJDIR)
	$(COMPILE.c) $< -o $@

$(STDLIBOBJDIR)/%.o: %.c ft_stdlib.h $(HEADER) | $(STDLIBOBJDIR)
	$(COMPILE.c) $< -o $@

$(WCHAROBJDIR)/%.o: %.c ft_wchar.h $(HEADER) | $(WCHAROBJDIR)
	$(COMPILE.c) $< -o $@

$(OTHEROBJDIR)/%.o: %.c other.h $(HEADER) | $(OTHEROBJDIR)
	$(COMPILE.c) $< -o $@

$(STRINGOBJDIR)/%.o: %.c ft_string.h $(HEADER)| $(STRINGOBJDIR)
	$(COMPILE.c) $< -o $@

$(HASHOBJDIR)/%.o: %.c ft_hash.h $(HEADER)| $(HASHOBJDIR)
	$(COMPILE.c) $< -o $@

$(BTREEOBJDIR)/%.o: %.c ft_btree.h $(HEADER)| $(BTREEOBJDIR)
	$(COMPILE.c) $< -o $@

$(UTESTOBJDIR)/%.o: %.c utest.h $(HEADER)| $(UTESTOBJDIR)
	$(COMPILE.c) $< -o $@

$(LIBOBJDIR):
	-mkdir -p $@
$(CTYPEOBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(STDIOOBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(STDLIBOBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(STRINGOBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(BUFFEROBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(WCHAROBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(LSTOBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(DLSTOBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(OTHEROBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(PRINTFOBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(HASHOBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(BTREEOBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@
$(UTESTOBJDIR): | $(LIBOBJDIR)
	-mkdir -p $@

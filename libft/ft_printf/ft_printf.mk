FT_PRINTF=\
buf.c\
buf_op.c\
char_op.c\
characters.c\
flag.c\
flag_p2.c\
flag_print.c\
flag_utils.c\
fpf_ptrget.c\
fpf_string.c\
ft_asprintf.c\
ft_atoi.c\
ft_bzero.c\
ft_printf.c\
ft_vprintf.c\
handle_bin.c\
handle_char.c\
handle_dec.c\
handle_exp.c\
handle_float.c\
handle_n.c\
handle_pct.c\
handle_ptr.c\
handle_str.c\
handle_uns.c\
handler.c\
padding.c\
print_dec.c\

FT_PRINTF_DIR=ft_printf

OBJ+=$(addprefix $(OBJDIR)/$(FT_PRINTF_DIR)/, $(FT_PRINTF:%.c=%.o))

SRCDIR+=$(FT_PRINTF_DIR)/

INCLUDE+=-I$(FT_PRINTF_DIR)/

HEADER=ft_printf.h

$(OBJDIR)/$(FT_PRINTF_DIR)/%.o: %.c $(HEADER) | $(OBJDIR)/$(FT_PRINTF_DIR)
	$(COMPILE.c) $< -o $@

$(OBJDIR)/$(FT_PRINTF_DIR):
	mkdir -p $(OBJDIR)/$(FT_PRINTF_DIR)

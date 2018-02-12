NAME:=exec
MAIN:=main_exec.c

CC:=gcc
CFLAGS:=-Wall -Wextra -Werror
ifeq ($(SANE),true)
CFLAGS+=-fsanitize=address -g3
endif
ifeq ($(SANE),g3)
CFLAGS+=-g3
endif

LIB_D:=../libs
OBJ_D:=obj
INC_D:=inc

INCLUDES:=\
-I../../includes\
-I../../lib21sh/ft_astr\
-I../../lib21sh/ft_ctype\
-I../../lib21sh/ft_dlst\
-I../../lib21sh/ft_hashset\
-I../../lib21sh/ft_list\
-I../../lib21sh/ft_string\
-I../../lib21sh/ft_stdio\
-I../../lib21sh/stack\
-I../../lib21sh/qbuf\
-I../../lib21sh/kvp\

LIBRARIES:=\
../../lib21sh/libft.a\
-lcurses

ITEM:=\
env_setup.o\
proc_chgstat.o\
proc_lifecycle.o\
proc_exec.o\
job_exec.o\
job_lifecycle.o\
job_utils.o\
get_path.o\
job_wait.o
OBJ:=$(addprefix $(OBJ_D)/, $(ITEM))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MAIN) $(LIBRARIES) $(INCLUDES)

$(OBJ_D)/%.o: %.c
	@mkdir -p $(OBJ_D)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	$(RM) -r $(OBJ_D)

fclean: clean
	$(RM) $(NAME)

re: fclean all

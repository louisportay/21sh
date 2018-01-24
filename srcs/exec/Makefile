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

LIB_D:=../../../libs
OBJ_D:=obj

INCLUDES:=\
	-I../../includes\
	-I$(LIB_D)/ft_mem/inc\
	-I$(LIB_D)/ft_string/inc\
	-I$(LIB_D)/ft_dlist/inc

LIBRARIES:=\
	$(LIB_D)/ft_mem/libftmem.a\
	$(LIB_D)/ft_string/libftstring.a

ITEM:=\
job_exec.o\
job_lifecycle.o\
job_utils.o\
main_exec.o\
proc_lifecycle.o
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

#gcc -Wall -Wextra -Werror main_exec.c -I../../includes -I../../../libs/ft_{mem,string,dlist}/inc ../../../libs/ft_{mem,string}/*.a ./job_exec.c ./job_lifecycle.c ./proc_lifecycle.c ./job_exec.c

NAME:=parser

CC:=gcc
CFLAGS:=-Wall -Wextra -Werror
ifeq ($(SANE),true)
CFLAGS+=-fsanitize=address -g3
endif
ifeq ($(SANE),g3)
CFLAGS+=-g3
endif

OBJ_D:=obj

INCLUDES:=\
-I../exec\
-I../../includes\
-I../../libft/includes\
-I../libs/ft_mem/inc\
-I../libs/ft_string/inc\
-I../libs/ft_astr/inc\
-I../libs/ft_hashset/inc\
-I../libs/qbuf/inc

LIBRARIES:=\
../libs/ft_astr/libftastr.a\
../libs/ft_mem/libftmem.a\
../../libft/libft.a

ITEMS:=\
parser.o\
update_env.o

OBJ:=$(addprefix $(OBJ_D)/, $(ITEMS))

vpath %.c .

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBRARIES) 

$(OBJ_D)/%.o: %.c
	@mkdir -p $(OBJ_D)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	$(RM) -r $(OBJ_D)

fclean: clean
	$(RM) $(NAME)

re: fclean all

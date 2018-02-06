CC:=gcc
CFLAGS:=-Wall -Werror -Wextra
NAME:=libfthashset.a

OBJ_D:=obj
SRC_D:=src
INC_D:=inc
LIB_D:=..

INC:=-I $(INC_D)

####
# FT_MEM
####

FT_MEM:=ft_mem
FT_MEM_DIR:=$(LIB_D)/$(FT_MEM)
FT_MEM_A:=libftmem.a
FT_MEM_LA:=$(FT_MEM_DIR)/$(FT_MEM_A)
FT_MEM_LIB:=-L $(FT_MEM_DIR) -lftmem
FT_MEM_INC:=-I $(FT_MEM_DIR)/$(INC_D)

####
# FT_STRING
####

FT_STRING:=ft_string
FT_STRING_DIR:=$(LIB_D)/$(FT_STRING)
FT_STRING_A:=libftstring.a
FT_STRING_LA:=$(FT_STRING_DIR)/$(FT_STRING_A)
FT_STRING_LIB:=-L $(FT_STRING_DIR) -lftstring
FT_STRING_INC:=-I $(FT_STRING_DIR)/$(INC_D)

RM:=/bin/rm
MK:=@/bin/mkdir

ITEMS:=\
	   ft_hashset.o\
	   ft_hashset_free.o
OBJ:=$(addprefix $(OBJ_D)/, $(ITEMS))

VPATH:=src:inc

INCLUDES:=\
		  $(INC)\
		  $(FT_STRING_INC)\
		  $(FT_MEM_INC)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) rc $@ $(OBJ)
	ranlib $@

$(OBJ_D)/%.o: %.c 
	$(MK) -p $(OBJ_D)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	$(RM) -rf $(OBJ_D)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

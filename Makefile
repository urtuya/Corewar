SRC_DIR = src/
SRC_FILES = main.c validation.c init.c
INC = inc/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))


all:
	gcc -g $(SRC) -I $(INC) libft/libft.a
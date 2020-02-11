SRC_DIR = src/
SRC_FILES = main.c validation.c init.c arena.c start.c print_info.c check.c op.c\
			operations.c
INC = inc/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))


all:
	gcc  -Wno-implicit-function-declaration -g $(SRC) -I $(INC) libft/libft.a

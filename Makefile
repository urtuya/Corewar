NAME = corewar
SRC_DIR = src/
SRC_FILES = main.c validation.c init.c init_main_struct.c in_cycle.c check.c op.c\
			operations13_16.c values_calculation.c print.c parse_args.c\
			operations1_3.c operations4_8.c operations9_12.c setting_ids.c\
			flags.c reading_bytes.c error.c
LIBFT_DIR = libft/
LIB = $(LIBFT_DIR)libft.a
INC = -I ./inc -I ./$(LIBFT_DIR)inc
FLAGGS = -Wall -Wextra -Werror
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))


all: $(NAME)

$(NAME): $(LIB)
	gcc -g $(FLAGGS) $(SRC) $(INC) $(LIB) -o $(NAME)


$(LIB):
	make -C $(LIBFT_DIR)

clean:
	rm -f *.gch
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all	

.PHONY: re all clean fclean

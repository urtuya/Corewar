SRC_DIR = src/
SRC_FILES = main.c validation.c init.c init_main_struct.c in_cycle.c check.c op.c\
			operations13_16.c values_calculation.c print.c parse_args.c\
			operations1_3.c operations4_8.c operations9_12.c setting_ids.c\
			flags.c reading_bytes.c error.c
LIBFT_DIR = libft
INC = inc/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
NAME = corewar


all:		$(NAME)

$(NAME):	$(SRC) $(LIBFT_DIR)
	make -C $(LIBFT_DIR)
	gcc $(SRC) -I $(INC) -I libft/inc $(LIBFT_DIR)/libft.a -o $(NAME)

clean:	
	make -C $(LIBFT_DIR) clean

fclean:
	make -C $(LIBFT_DIR) fclean
	rm -rf corewar

re:		fclean all

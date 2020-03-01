# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydavis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/01 14:45:58 by ydavis            #+#    #+#              #
#    Updated: 2020/03/01 15:26:42 by vellery-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC_DIR = src/
SRC_FILES = main.c validation.c init.c init_main_struct.c in_cycle.c check.c op.c\
			operations13_16.c values_calculation.c print.c parse_args.c\
			operations1_3.c operations4_8.c operations9_12.c setting_ids.c\
			flags.c reading_bytes.c error.c
LIBFT_DIR = libft
LIB = libft.a
INC = inc/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))


all:		$(NAME)

$(NAME):	$(SRC) $(LIBFT_DIR)
	@make -C $(LIBFT_DIR)
	@gcc $(SRC) -I $(INC) -I $(LIBFT_DIR)/$(INC) $(LIBFT_DIR)/$(LIB) -o $(NAME)

clean:	
	@make -C $(LIBFT_DIR) clean

fclean:
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re:		fclean all

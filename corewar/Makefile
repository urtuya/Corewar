# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydavis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/01 16:07:01 by ydavis            #+#    #+#              #
#    Updated: 2020/03/01 20:06:21 by ydavis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM=asm
COREWAR=corewar
ASM_DIR=ASM_DIR/
COREWAR_DIR=VM/

all: $(ASM) $(COREWAR) 

$(ASM):
	make -C $(ASM_DIR)
	cp $(addprefix $(ASM_DIR), $(ASM)) .

$(COREWAR):
	make -C $(COREWAR_DIR)
	cp $(addprefix $(COREWAR_DIR), $(COREWAR)) .

clean:
	make clean -C $(ASM_DIR)
	make clean -C $(COREWAR_DIR)

fclean:
	make fclean -C $(ASM_DIR)
	make fclean -C $(COREWAR_DIR)
	rm -f $(ASM)
	rm -f $(COREWAR)

re:		fclean all

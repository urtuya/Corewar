NAME = libft.a

LIB_CFILES = ft_atoi.c ft_lstdel.c ft_memcpy.c\
		 ft_putnbr_fd.c ft_strdup.c ft_strncat.c\
		 ft_strsub.c ft_bzero.c ft_lstdelone.c ft_memdel.c\
		 ft_putstr.c ft_strequ.c ft_strncmp.c ft_strtrim.c\
		 ft_isalnum.c ft_lstiter.c ft_memmove.c ft_putstr_fd.c\
		 ft_striter.c ft_strncpy.c ft_tolower.c\
		 ft_isalpha.c ft_lstmap.c ft_memset.c ft_strcat.c\
		 ft_striteri.c ft_strnequ.c ft_toupper.c\
		 ft_isascii.c ft_strlcpy.c ft_strndup.c\
		 ft_lstnew.c ft_putchar.c ft_strchr.c ft_strjoin.c\
		 ft_strnew.c ft_isdigit.c ft_memalloc.c ft_putchar_fd.c\
		 ft_strclr.c ft_strlcat.c ft_strnstr.c ft_isprint.c\
		 ft_memccpy.c ft_putendl.c ft_strcmp.c ft_strlen.c\
		 ft_strrchr.c ft_itoa.c ft_memchr.c ft_putendl_fd.c\
		 ft_strcpy.c ft_strmap.c ft_strsplit.c ft_lstadd.c\
		 get_next_line.c ft_memcmp.c ft_putnbr.c ft_strdel.c\
		 ft_strmapi.c ft_strstr.c ft_ex_arrdel.c ft_ex_matdel.c\
		 ft_ex_prnt.c ft_ex_prnt_arr.c ft_change_val.c ft_matrix.c\
		 ft_ftoa.c intmax_toa.c uintmax_toa.c ft_freesplit.c ft_swap.c\
		 ft_min_max.c ft_strnjoin.c ft_isspace.c ft_atoi_base.c\
		 lower_upper.c ft_isnumber.c
PRINTF_CFILES = adding_to_buf.c color.c ft_printf.c helping.c print_char.c\
				print_d.c print_f.c print_o_x_b.c print_p.c print_unsign.c\
				set_all_fields.c set_len_type.c unsigned_addchar.c ft_fprintf.c

FLAGGS = -Wall -Wextra -Werror
HFILES = libft.h ft_printf.h ft_fprintf.h get_next_line.h
INC_DIR = inc/
PRINTF_DIR = ft_printf/
SRC_DIR = src/
OBJ_DIR = obj/
INC = $(addprefix $(INC_DIR), $(HFILES))
SRC = $(addprefix $(SRC_DIR), $(LIB_CFILES)) $(addprefix $(PRINTF_DIR), $(PRINTF_CFILES))
OBJ = $(addprefix $(OBJ_DIR), $(LIB_CFILES:.c=.o)) $(addprefix $(OBJ_DIR), $(PRINTF_CFILES:.c=.o))


all: $(NAME)

$(NAME):  $(OBJ_DIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@gcc -c $(FLAGGS) -I $(INC_DIR) $< -o $@

$(OBJ_DIR)%.o: $(PRINTF_DIR)%.c $(INC)
	@gcc -c $(FLAGGS) -I $(INC_DIR) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf *.h.gch

fclean: clean
	@rm -rf $(NAME) 

re: fclean all

.PHONY: re, fclean, clean, all

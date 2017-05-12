NAME = asm
LIBFT = ../libft/libft.a
OBJ = ft_error.o ft_validation_head.o header_bc.o inline_fts_bc_header.o \
		main.o write_bc_to_header.o compile_to_hex.o hash.o g_op.o \
		compile_to_hex_addition.o all_delims_split.o ft_arg_to_binary.o \
		ft_create_comand_struct.o ft_read_comand.o ft_read_comand_2.o \
		ft_valid_arguments.o
CC = gcc
CCFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./ -I../ -I../libft

.phony: all clean fclean re

all: $(OBJ) $(LIBFT)
	@ $(CC) $(CCFLAGS) $(LIBFT) $(OBJ) -o $(NAME)
	@ echo "\x1b[01;32mAsm was successfully compiled\x1b[0m"

$(LIBFT):
	@ make -C ../libft

%.o : ./%.c
	@ gcc -g -Wall -Wextra -Werror -o $@ -c $< $(INCLUDES)

clean:
	@ make clean -C ../libft
	@ /bin/rm -f $(OBJ)

fclean: clean
	@ /bin/rm -f ../libft/libft.a
	@ /bin/rm -f $(NAME)
	@ echo "\033[01;31mAsm files deleted\x1b[0m"

re: fclean all

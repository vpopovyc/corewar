# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/22 19:20:38 by vpopovyc          #+#    #+#              #
#    Updated: 2017/05/22 19:20:43 by vpopovyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm
LIBFT = ../libft/libft.a
OBJ = asm_src/init_validation.o asm_src/main.o asm_src/file_utils.o ../op.o \
		asm_src/enqueue_labels.o stack/queue.o stack/stack.o \
		asm_src/separ_delim.o asm_src/hash_labels.o hash/hash.o \
		asm_src/compilation.o asm_src/insert_arg.o hash/hash_id.o \

CC = clang
CCFLAGS = -Wall -Wextra -Werror
INCLUDES = -I../ -I../libft -I./headers

.phony: all clean fclean re

all: $(OBJ) $(LIBFT)
	 $(CC) $(CCFLAGS) $(LIBFT) $(OBJ) -o $(NAME)
	@ echo "\x1b[01;32mAsm was successfully compiled\x1b[0m"

$(LIBFT):
	@ make -C ../libft

%.o : ./%.c
	 clang -g -Wall -Wextra -Werror -o $@ -c $< $(INCLUDES)

clean:
	@ make clean -C ../libft
	@ /bin/rm -f $(OBJ)

fclean: clean
	@ /bin/rm -f ../libft/libft.a
	@ /bin/rm -f $(NAME)
	@ echo "\033[01;31mAsm files deleted\x1b[0m"

re: fclean all

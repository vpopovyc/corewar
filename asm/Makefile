# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/22 19:20:38 by vpopovyc          #+#    #+#              #
#    Updated: 2017/06/05 19:38:08 by rvolovik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm
LIBFT = ../libft/libft.a
OBJ = asm_src/init_validation.o asm_src/main.o asm_src/file_utils.o ../op.o \
		asm_src/enqueue_labels.o stack/queue.o stack/stack.o \
		asm_src/separ_delim.o asm_src/hash_labels.o hash/hash.o \
		asm_src/compilation.o asm_src/insert_arg.o hash/hash_id.o \
		sounds/sounds.o

CC = clang
CCFLAGS = -g -Wall -Wextra -Werror -framework SDL2
INCLUDES = -I../ -I../libft -I./headers
OBJCCFALGS = -g -Wall -Wextra -Werror

.phony: all clean fclean re

all: $(LIBFT) $(OBJ) 
	$(CC) $(CCFLAGS) $(LIBFT) $(OBJ) -o $(NAME)
	@ echo "\x1b[01;32mAsm was successfully compiled\x1b[0m"

$(LIBFT):
	@ make -C ../libft

%.o : ./%.c
	 $(CC) $(INCLUDES) $(OBJCCFALGS) -o $@ -c $<

clean:
	@ make -C ../libft clean
	@ /bin/rm -f $(OBJ)
	@ echo "\033[01;31mAsm objects deleted\x1b[0m"

fclean:
	@ make -C ../libft fclean
	@ /bin/rm -f $(OBJ)
	@ echo "\033[01;31mAsm objects deleted\x1b[0m"
	@ /bin/rm -f $(NAME)
	@ echo "\033[01;31mAsm binary  deleted\x1b[0m"

re: fclean all

NAME = disassemble

SRC = decode_bytes.c dissassemble_comands.c ft_create_file_and_write.c \
		ft_valid_name_comment.c main.c parse_args.c ../op.c \

OBJ = $(SRC:.c=.o)

INC = -I./ -I../libft/includes -I../

CFLAGS = -Wall -Wextra -Werror

CC = gcc

LIBFT = ../libft/libft.a

.phony: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(LIBFT) $(CFLAGS) $(OBJ) -o $(NAME)

$(LIBFT):
	make -C ../libft/

%.o: %.c
	gcc -c -o $@ $<

clean:
	make -C ../libft/ clean
	rm -rf $(OBJ)

fclean: clean
	make -C ../libft/ fclean
	rm -f $(NAME)

re: fclean all

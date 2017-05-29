# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/12 15:22:31 by dkosolap          #+#    #+#              #
#    Updated: 2017/05/29 11:13:09 by dkosolap         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
LIB = -L../libft -lft
FLAG = -Wall -Wextra -Werror
SRC = corewar.c dk_pars_arg.c ft_valid_cor.c ft_create_field_and_carriage.c \
	ft_algoritm.c ../op.c \
	commands/ft_comand_function.c commands/ft_and_or_xor.c commands/ft_sti.c
BINS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(BINS)
	make -C ../libft
	gcc $(LIB) $(FLAG) $(BINS) -o $(NAME)
%.o: %.c
	gcc -c -o $@ $<
clean:
	make -C ../libft/ clean
	rm -rf $(BINS)
fclean: clean
	make -C ../libft/ fclean
	rm -f $(NAME)
re: fclean all

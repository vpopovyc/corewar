# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/12 15:22:31 by dkosolap          #+#    #+#              #
#    Updated: 2017/05/29 18:03:40 by dkosolap         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
LIB = -L../libft -lft
FLAG = -g -Wall -Wextra -Werror
SRC = corewar.o dk_pars_arg.o ft_valid_cor.o ft_create_field_and_carriage.o \
	ft_algoritm.o ../op.o dk_sort_ply.o ft_comand_function.o \
	commands/ft_add.o commands/ft_aff.o commands/ft_and_or_xor.o \
	commands/ft_fork.o commands/ft_ld.o commands/ft_ldi_lldi.o \
	commands/ft_lfork.o commands/ft_live.o commands/ft_lld.o commands/ft_st.o \
	commands/ft_sti.o commands/ft_sub.o commands/ft_zjmp.o

all: $(NAME)

$(NAME): $(SRC)
	make -C ../libft
	gcc $(LIB) $(FLAG) $(SRC)  -o $(NAME)
%.o: %.c
	gcc -c  -I../ -o $@ $<
clean:
	make -C ../libft/ clean
	rm -rf $(BINS)
fclean: clean
	make -C ../libft/ fclean
	rm -f $(NAME)
re: fclean all

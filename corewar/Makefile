# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/12 15:22:31 by dkosolap          #+#    #+#              #
#    Updated: 2017/06/02 17:36:52 by dkosolap         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
LIB = -L../libft -lft -I./ncurses/sounds -I./ncurses
OBJFLAG = -Wall -Wextra -Werror
FLAG =  -Wall -Wextra -Werror -framework SDL2 -lpthread -lncurses 

SRC = corewar.o dk_pars_arg.o ft_valid_cor.o ft_create_field_and_carriage.o \
	ft_algoritm.o ../op.o dk_sort_ply.o ft_comand_function.o ft_take_ind.o\
	commands/ft_add.o commands/ft_aff.o commands/ft_and_or_xor.o \
	commands/ft_fork.o commands/ft_ld.o commands/ft_ldi_lldi.o \
	commands/ft_lfork.o commands/ft_live.o commands/ft_lld.o commands/ft_st.o \
	commands/ft_sti.o commands/ft_sub.o commands/ft_zjmp.o ft_algoritm_2.o \
	commands/ft_and_or_xor_2.o

VIS = ncurses/algo_event_managment.o ncurses/fill_screen.o ncurses/init_screen.o \
	ncurses/usage_status_credits.o ncurses/visualisation.o ncurses/sounds/sounds.o \
	ncurses/algo_event_managment_addition.o

SRC += $(VIS)

all: $(NAME)

$(NAME): $(SRC)
	make -C ../libft
	clang $(LIB) $(FLAG) $(SRC)  -o $(NAME)
%.o: %.c
	clang -c $(OBJFLAG) -I../ -o $@ $<
clean:
	make -C ../libft/ clean
	rm -rf $(SRC)
fclean: clean
	make -C ../libft/ fclean
	rm -f $(NAME)
re: fclean all

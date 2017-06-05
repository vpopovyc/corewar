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

OBJ = corewar.o dk_pars_arg.o ft_valid_cor.o ft_create_field_and_carriage.o \
	ft_algoritm.o ../op.o dk_sort_ply.o ft_comand_function.o ft_take_ind.o\
	commands/ft_add.o commands/ft_aff.o commands/ft_and_or_xor.o \
	commands/ft_fork.o commands/ft_ld.o commands/ft_ldi_lldi.o \
	commands/ft_lfork.o commands/ft_live.o commands/ft_lld.o commands/ft_st.o \
	commands/ft_sti.o commands/ft_sub.o commands/ft_zjmp.o ft_algoritm_2.o \
	commands/ft_and_or_xor_2.o

VIS = ncurses/algo_event_managment.o ncurses/fill_screen.o ncurses/init_screen.o \
	ncurses/usage_status_credits.o ncurses/visualisation.o ncurses/sounds/sounds.o \
	ncurses/algo_event_managment_addition.o

OBJ += $(VIS)

CC = clang
LIBFT = ../libft/libft.a
LIB = -Wall -Wextra -Werror -framework SDL2 -lpthread -lncurses  
CCFLAGS =  -Wall -Wextra -Werror -framework SDL2
INCLUDES = -I../ -I../libft -I./ncurses/sounds -I./ncurses
OBJCCFALGS = -Wall -Wextra -Werror

.phony: all clean fclean re

all: $(LIBFT) $(OBJ) 
	$(CC) $(CCFLAGS) $(LIB) $(LIBFT) $(OBJ) -o $(NAME)
	@ echo "\x1b[01;32mCorewar was successfully compiled\x1b[0m"

$(LIBFT):
	@ make -C ../libft

%.o : ./%.c
	 $(CC) $(OBJCCFALGS) $(INCLUDES) -o $@ -c $<

clean:
	@ make -C ../libft clean
	@ /bin/rm -f $(OBJ)
	@ echo "\033[01;31mCorewar objects deleted\x1b[0m"

fclean:
	@ make -C ../libft fclean
	@ /bin/rm -f $(OBJ)
	@ echo "\033[01;31mCorewar objects deleted\x1b[0m"
	@ /bin/rm -f $(NAME)
	@ echo "\033[01;31mCorewar binary  deleted\x1b[0m"

re: fclean all

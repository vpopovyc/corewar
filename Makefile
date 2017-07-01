# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/08 11:33:51 by dkosolap          #+#    #+#              #
#    Updated: 2017/06/08 11:38:51 by dkosolap         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm/

DISASM = disassembler/

CW = corewar/

.phony: all clean fclean re

all:
	make -C $(ASM)
	make -C $(DISASM)
	make -C $(CW)

clean:
	make clean -C $(ASM)
	make clean -C $(DISASM)
	make clean -C $(CW)

fclean: clean
	make fclean -C $(ASM)
	make fclean -C $(DISASM)
	make fclean -C $(CW)

re: fclean
	make re -C $(ASM)
	make re -C $(DISASM)
	make re -C $(CW)
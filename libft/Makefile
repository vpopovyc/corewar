# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/24 15:22:42 by vpopovyc          #+#    #+#              #
#    Updated: 2017/03/23 18:42:30 by vpopovyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isprintf_spec.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memset.c ft_memcpy.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memset.c ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c \
		ft_strncpy.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c \
		ft_strlen.c ft_strncat.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strstr.c ft_tolower.c ft_toupper.c ft_memalloc.c ft_memdel.c \
		ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
	   	ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
		ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
		ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_do_op.c ft_intzero.c \
		ft_re_alloc.c ft_strnfjoin.c ft_atosize_t.c ft_isprintf_spec.c \
		ft_isprintf_up_spec.c ft_sstoab.c ft_stoab.c ft_psn.c ft_pssn.c \
		ft_iscl_group1.c ft_iscl_group2.c ft_loweralize.c ft_capitalize.c \
		ft_wstrlen.c ft_iscl_group3.c ft_wstrblen.c ft_uct8.c ft_pspp.c \
		ft_wstrmem.c ft_ppdel.c format.c ft_s_printf.c ft_group_onetwo.c \
		ft_bit_party.c ft_making_move.c ft_group_united.c get_next_line.c \
		ft_strndup.c ft_power.c ft_charstc.c ft_atoi_base.c ft_ishex.c \
		ft_chexlen.c ft_issign.c f_format.c ft_s_fprintf.c ft_f_group_onetwo.c \
		ft_f_bit_party.c ft_f_making_move.c ft_f_group_united.c ft_pspp_fd.c \
		ft_psn_fd.c ft_pssn_fd.c ft_parse.c ft_s_fdf.c ft_gradient.c \
		ft_init_image.c ft_draw_aa_line.c ft_drawpixel.c ft_keycodes.c \
		ft_modify_xyz.c ft_fdf.c ft_strclen.c

INC = includes/libft.h

OBJ = $(SRC:.c=.o) 

CFLAGS = -c -Wall -Wextra -Werror

all:  $(NAME)

$(NAME): $(OBJ)
	@echo "\x1b[32mObjects created\x1b[0m"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo  "\x1b[32mLibft   compiled\x1b[0m"

%.o: %.c
	@gcc -I $(INC) $(CFLAGS) -o $@ $<

clean:
	@echo "\033[01;31mObjects deleted\x1b[0m"
	@rm -f $(OBJ)

fclean: clean
	@echo "\033[01;31mLibtf   deleted\x1b[0m"
	@rm -f $(NAME)

re: fclean all

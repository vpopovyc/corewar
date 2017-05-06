/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_code_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:49:01 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/06 15:46:22 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BYTE_CODE_HEADER_H
# define __BYTE_CODE_HEADER_H

# include "../libft/includes/libft.h"
# include "../op.h"
/*
** Header magic
*/
# define TWO_BYTES_SPR 				4
# define MAX_UINT_SIZE 				9
# define BASE						16
# define HIGH_FOUR_BITS				28
# define HEX_CHARS					"0123456789abcdef"
/*
** Header name
*/
# define BEGIN_OF_LINE				0
# define NO_SPACE					1
# define BEGIN_OF_LINE_AFTER_MAGIC	4
# define SPACE_NEEDED 				4
# define NEW_LINE_NEEDED			16
# define BC_PROG_LENGTH 			PROG_NAME_LENGTH + (PROG_NAME_LENGTH / 2)
/*
** Header program size
*/
# define PROG_SIZE 					0x82828282
/*
** Header comment
*/
# define BC_COMMENT_LENGTH			COMMENT_LENGTH + (COMMENT_LENGTH / 2)
# define BEGIN_OF_LINE_AFTER_PS		12
/*
** Comands
*/
# define LIVE "live"
# define LD "ld"
# define ST "st"
# define ADD "add"
# define SUB "sub"
# define AND "and"
# define OR "or"
# define XOR "xor"
# define ZJMP "zjmp"
# define LDI "ldi"
# define STI "sti"
# define FORK "fork"
# define LLD "lld"
# define LLDI "lldi"
# define LFORK "lfork"
# define AFF "aff"

typedef struct		s_comand
{
	char			*name;
	int				op_code;
	char			*arg1;
	char			*arg2;
	char			*arg3;
	char			*hex_code;
	struct s_comand *next;
}					t_comand;

typedef struct		s_label_list
{
	char			*name;
	t_comand		*comand;
	struct s_label_list *next;
}					t_label;

/*
** Struct that contain header bc
*/
typedef struct		s_bc_header
{
  char				magic[MAX_UINT_SIZE + 1];
  char				prog_name[BC_PROG_LENGTH + 1];
  char				prog_size[MAX_UINT_SIZE + 1];
  char				comment[BC_COMMENT_LENGTH + 1];
}					t_bc_header;
/*
** main.c
*/
void		header_bc_init(t_bc_header *sv, header_t *header);
/*
** inline_fts_bc_header.c
*/
char 		char_to_hex(char pv);
char 		erase_high_bits(char pv);
char 		erase_low_bits(char pv);
int 		find_num_of_bytes(int length);
/*
** write_bc_to_header.c
*/
int 		count_number_of_bytes(int key_length);
void		variables_moves(int *space, int *new_line, int *i);
void		write_bc_to_header(char **prog, char **reference, int i);
void		place_new_line(char *prog_name, int *space, int *new_line);
void		place_space(char *prog_name, int *space);
/*
** Validation struct
*/
typedef struct		s_gamer
{
	header_t		*src;
	t_bc_header		*header_bc;
	t_label			*label;
	char			*name;
	char			*comment;
	int				header;
	int				fd;
	unsigned int	len_def_name;
	unsigned int	len_def_comment;
}					t_gamer;

t_label     *ft_add_label(void); /////////////
t_comand    *ft_add_comand(void); ///
int		ft_valid_comand_arguments(char *src, char **arg); //////
void    ft_write_comands(t_gamer *src, int i, char *tmp);

/*
** ft_error.c
*/
void			ft_error(int n);
int				ft_isspace(char c);
/*
** ft_validation_header.c
*/
void			ft_validation(t_gamer *src);
#endif

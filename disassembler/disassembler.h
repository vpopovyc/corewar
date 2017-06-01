/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 17:31:10 by rvolovik          #+#    #+#             */
/*   Updated: 2017/06/01 15:47:47 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DISASSEMBLER_H
# define _DISASSEMBLER_H

# include "../libft/includes/libft.h"
# include "../op.h"

# define ARGSNUM	3

# define FIRSTARG	6
# define SECONDARG	4
# define THIRDARG	2

# define FMASK		192
# define SMASK		48
# define TMASK		12

# define REGCHAR	"r"
# define DIRCHAR	"%"

typedef struct		s_comand
{
	char			name;
	char			**arg;
	struct s_comand	*next;
}					t_comand;

typedef struct		s_desasm
{
	char			*file_name;
	char			*file_data;
	ssize_t			file_len;
	t_comand		*comands_list;
	char			*name;
	char			*comment;
	unsigned int	len_comands_code;
	unsigned int	curent_position;
	int				fd;
}					t_desasm;

void				ft_valid_name_comment(t_desasm *data);
void				ft_error(int n);

/*
**	dissassemble_comands.c
*/

void				dissassemble_comands(t_desasm *data);

/*
**	ft_create_file_and_write.c
*/

void				ft_create_file_and_write(t_desasm *data);

/*
**	parse_args.c
*/

char				*form_direct(char *file, unsigned int *pos, int com_ind);
char				*parse_args(char t_arg, char *file, unsigned int *pos,
								int com_ind);

/*
**	decode_bytes.c
*/

int					count_bytes(char byte, char com_ind);
int					write_to_int(char *file, unsigned int *pos);
int					write_to_short(char *file, unsigned int *pos);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_code_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 20:29:55 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/06/05 14:38:46 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BYTE_CODE_HEADER_H
# define __BYTE_CODE_HEADER_H

# include "../../op.h"
# include "../../libft/includes/libft.h"
# include "stack.h"
# include "hash.h"

/*
**	COMMANDS DEFINE
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

/*
** FILE DESRIPTORS
*/

extern int g_fd_s;
extern int g_fd_cor;
extern int g_line;

/*
**	BASE STRUCTURE
*/

typedef struct		s_base
{
	t_header		*reference;
	t_hash			*table;
	t_stack			q_label;
	char			*path;
}					t_base;

/*
** main.c
*/

void				find_delete_comment(char *ln);
void				ft_error(int n, int line);
void				check_new_line(int fd);

/*
** file_utils.c
*/

int					ft_isspace(int c);
char				*obrezka_stroki(char *line);
void				skip_spaces(char **line);
char				*filepath(char *str);
char				*ft_open(char *name);
int					command_length(char opcode);

/*
** init_validation.c
*/

# define QUOTE 			'\"'
# define HEADER_PARTS 	2

t_base				*init_validation(char *av);

/*
**	enqueue_labels.c
*/

t_stack				*enqueue_labels(t_stack *queue, t_hash *table,
													unsigned int *prog_size);

/*
**	compilation.c
*/

void				compilation(t_hash *tb, t_stack *q_lb,
													t_header *re, char *path);

#endif

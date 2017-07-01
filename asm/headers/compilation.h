/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compilation.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:39:57 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/22 18:39:59 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COMPILATION_H
# define __COMPILATION_H

# include "byte_code_header.h"
# include "hash.h"

# define USER_RIGHTS O_CREAT | O_RDWR | O_TRUNC, S_IRWXG | S_IRWXO | S_IRWXU
# define FIRSTARG	6
# define SECONDARG	0x3F
# define THIRDARG 	0xF
# define C_TAKAYA_C	3

/*
** Globals
*/

extern int	g_fd_cor;
extern int	g_carrige;
/*
** insert_args.c
*/

void	insert_args(char hex_code, char *arg, t_hash *table, char opcode);
void	insert_direct(char *arg, char label_size, t_hash *table);
void	insert_indirect(char *ind, t_hash *table);
void	insert_registres(char *reg);

/*
** compilation.c
*/

void	labels_compile(t_hash *table, t_stack *q_labels);
void	print_command(t_command *com, t_hash *table);
void	print_label(char *arg, char label_size, t_hash *table);
void	uint_compile(unsigned int n);
#endif

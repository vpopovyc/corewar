/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 10:53:53 by dkosolap          #+#    #+#             */
/*   Updated: 2017/05/08 10:53:54 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __COREWAR_H
# define __COREWAR_H

#include "../op.h"
#include "../libft/includes/libft.h"
#include "stdio.h"

typedef struct		s_player
{
	int				magic;
	char			name[128];
	char			comment[2048];
	char			code;
	int				number;
	int				size;
	struct s_player	*next;
}					t_player;

typedef struct		s_op
{
	char			*name;
	int				binary_code;
	int				len[3];
	int				op_code;
	int				cycle;
	char			*comment;
	int				octal;
	int				dependence_carry;
}					t_op;

typedef struct		s_carriage
{
	t_op 			(*f)(int a, int b, int c);
}					t_carriage;

typedef struct		s_corewar
{
	t_player		*players;
	int				cycle;
	int				cycle_to_die;
	int				cycle_delta;
	int				fdump;
	int				verbose;
}					t_corewar;

#endif 
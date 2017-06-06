/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and_or_xor_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 12:04:56 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/06 16:15:33 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void		ft_and_or_xor_5(t_corewar *d, t_carriage *s, char op, char c)
{
	if (c == -12 && s->arg[3] >= 0 && s->arg[3] <= REG_NUMBER)
	{
		s->arg[1] = ft_take_ind(d, (s->position - 7 + s->arg[1]));
		s->arg[2] = ft_take_ind(d, (s->position - 7 + s->arg[2]));
		(op == 6) ? (s->reg[s->arg[3]] = s->arg[1] & s->arg[2]) : 0;
		(op == 7) ? (s->reg[s->arg[3]] = s->arg[1] | s->arg[2]) : 0;
		(op == 8) ? (s->reg[s->arg[3]] = s->arg[1] ^ s->arg[2]) : 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
	else if (c == -28 && s->arg[3] >= 0 && s->arg[3] <= REG_NUMBER)
	{
		s->arg[1] = ft_take_ind(d, (s->position - 9 + s->arg[1]));
		(op == 6) ? (s->reg[s->arg[3]] = s->arg[1] & s->arg[2]) : 0;
		(op == 7) ? (s->reg[s->arg[3]] = s->arg[1] | s->arg[2]) : 0;
		(op == 8) ? (s->reg[s->arg[3]] = s->arg[1] ^ s->arg[2]) : 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
}

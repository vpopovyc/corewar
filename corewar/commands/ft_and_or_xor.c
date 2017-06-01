/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and_or_xor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 12:42:56 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/01 12:44:42 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

static void	ft_and_or_xor_1(t_carriage *s, char op)
{
	if (s->arg[1] >= 0 && s->arg[1] <= REG_NUMBER && s->arg[2] >= 0 && s->arg[2]
		<= REG_NUMBER && s->arg[3] && s->arg[3] <= REG_NUMBER)
	{
		(op == 6) ? (s->reg[s->arg[3]] = s->reg[s->arg[1]] & s->reg[s->arg[2]])
			: 0;
		(op == 7) ? (s->reg[s->arg[3]] = s->reg[s->arg[1]] | s->reg[s->arg[2]])
			: 0;
		(op == 8) ? (s->reg[s->arg[3]] = s->reg[s->arg[1]] ^ s->reg[s->arg[2]])
			: 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
}

static void	ft_and_or_xor_2(t_corewar *d, t_carriage *s, char op, char c)
{
	if (c == -108 && s->arg[2] >= 0 && s->arg[2] <= REG_NUMBER && s->arg[3]
		>= 0 && s->arg[3] <= REG_NUMBER)
	{
		(op == 6) ? (s->reg[s->arg[3]] = s->arg[1] & s->reg[s->arg[2]]) : 0;
		(op == 7) ? (s->reg[s->arg[3]] = s->arg[1] | s->reg[s->arg[2]]) : 0;
		(op == 8) ? (s->reg[s->arg[3]] = s->arg[1] ^ s->reg[s->arg[2]]) : 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
	else if (c == -44 && s->arg[2] >= 0 && s->arg[2] <= REG_NUMBER && s->arg[3]
			>= 0 && s->arg[3] <= REG_NUMBER)
	{
		s->arg[1] = (s->position - 5 + s->arg[1]) % MEM_SIZE;
		(op == 6) ? (s->reg[s->arg[3]] = ((d->field[s->arg[1]] << 8) |
			d->field[s->arg[1] + 1]) & s->reg[s->arg[2]]) : 0;
		(op == 7) ? (s->reg[s->arg[3]] = ((d->field[s->arg[1]] << 8) |
			d->field[s->arg[1] + 1]) | s->reg[s->arg[2]]) : 0;
		(op == 8) ? (s->reg[s->arg[3]] = ((d->field[s->arg[1]] << 8) |
			d->field[s->arg[1] + 1]) ^ s->reg[s->arg[2]]) : 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
}

static void	ft_and_or_xor_3(t_corewar *d, t_carriage *s, char op, char c)
{
	if (c == 116 && s->arg[1] >= 0 && s->arg[1] <= REG_NUMBER && s->arg[3] >= 0
		&& s->arg[3] <= REG_NUMBER)
	{
		s->arg[1] = (s->position - 5 + s->arg[2]) % MEM_SIZE;
		(op == 6) ? (s->reg[s->reg[3]] = d->field[s->arg[2]] &
			s->reg[s->arg[1]]) : 0;
		(op == 7) ? (s->reg[s->reg[3]] = d->field[s->arg[2]] |
			s->reg[s->arg[1]]) : 0;
		(op == 8) ? (s->reg[s->reg[3]] = d->field[s->arg[2]] ^
			s->reg[s->arg[1]]) : 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
	else if (c == 100 && s->arg[1] >= 0 && s->arg[1] <= REG_NUMBER && s->arg[3]
		>= 0 && s->arg[3] <= REG_NUMBER)
	{
		(op == 6) ? (s->reg[s->arg[3]] = s->arg[1] & s->arg[2]) : 0;
		(op == 7) ? (s->reg[s->arg[3]] = s->arg[1] | s->arg[2]) : 0;
		(op == 8) ? (s->reg[s->arg[3]] = s->arg[1] ^ s->arg[2]) : 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
}

static void	ft_and_or_xor_4(t_corewar *d, t_carriage *s, char op, char c)
{
	if (c == -76 && s->arg[3] >= 0 && s->arg[3] <= REG_NUMBER)
	{
		s->arg[2] = (s->position - 8 + s->arg[2]) % MEM_SIZE;
		(op == 6) ? (s->reg[s->arg[3]] = s->arg[1] & d->field[s->arg[2]])
			: 0;
		(op == 7) ? (s->reg[s->arg[3]] = s->arg[1] | d->field[s->arg[2]])
			: 0;
		(op == 8) ? (s->reg[s->arg[3]] = s->arg[1] ^ d->field[s->arg[2]])
			: 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
	else if (c == -92 && s->arg[3] >= 0 && s->arg[3] <= REG_NUMBER)
	{
		(op == 6) ? (s->reg[s->arg[3]] = s->arg[1] & s->arg[2]) : 0;
		(op == 7) ? (s->reg[s->arg[3]] = s->arg[1] | s->arg[2]) : 0;
		(op == 8) ? (s->reg[s->arg[3]] = s->arg[1] ^ s->arg[2]) : 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
}

static void	ft_and_or_xor_5(t_corewar *d, t_carriage *s, char op, char c)
{
	if (c == -12 && s->arg[3] >= 0 && s->arg[3] <= REG_NUMBER)
	{
		s->arg[1] = (s->position - 6 + s->arg[1]) % MEM_SIZE;
		s->arg[2] = (s->position - 6 + s->arg[2]) % MEM_SIZE;
		(op == 6) ? (s->reg[s->arg[3]] = d->field[s->arg[1]] &
			d->field[s->arg[2]]) : 0;
		(op == 7) ? (s->reg[s->arg[3]] = d->field[s->arg[1]] |
			d->field[s->arg[2]]) : 0;
		(op == 8) ? (s->reg[s->arg[3]] = d->field[s->arg[1]] ^
			d->field[s->arg[2]]) : 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
	else if (c == -28 && s->arg[3] >= 0 && s->arg[3] <= REG_NUMBER)
	{
		s->arg[1] = (s->position - 8 + s->arg[1]) % MEM_SIZE;
		(op == 6) ? (s->reg[s->arg[3]] = s->arg[2] & d->field[s->arg[1]])
			: 0;
		(op == 7) ? (s->reg[s->arg[3]] = s->arg[2] | d->field[s->arg[1]])
			: 0;
		(op == 8) ? (s->reg[s->arg[3]] = s->arg[2] ^ d->field[s->arg[1]])
			: 0;
		s->carry = (s->reg[s->arg[3]] == 0) ? 1 : 0;
	}
}

void	ft_and_or_xor(t_corewar *d, t_carriage *s)
{
	char operation;
	char op_code;

	operation = d->field[s->position];
	op_code = d->field[s->position + 1];
	if (op_code == 84 || op_code == -108 || op_code == -44 || op_code == 116 ||
		op_code == 100 || op_code == -76 || op_code == -92 || op_code == -12 ||
		op_code == -28)
		ft_take_arg(d, s, 0, d->field[s->position + 1]);
	if (op_code == 84)
		ft_and_or_xor_1(s, operation);
	else if (op_code == -108 || op_code == -44)
		ft_and_or_xor_2(d, s, operation, op_code);
	else if (op_code == 116 || op_code == 100)
		ft_and_or_xor_3(d, s, operation, op_code);
	else if (op_code == -76 || op_code == -92)
		ft_and_or_xor_4(d, s, operation, op_code);
	else if (op_code == -12 || op_code == -28)
		ft_and_or_xor_5(d, s, operation, op_code);
	else
		ft_inc_index(s);
	ft_bzero(s->arg, 16);
}

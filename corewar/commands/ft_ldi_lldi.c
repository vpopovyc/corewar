/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi_lldi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 12:57:01 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/03 12:08:34 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	ft_get_data(t_corewar *data, t_carriage *src, int index, char comd)
{
	src->reg[src->arg[3]] = ((unsigned char)data->field[ft_fix(index)] << 24)
		| ((unsigned char)data->field[ft_fix(index + 1)] << 16) |
		((unsigned char)data->field[ft_fix(index + 2)] << 8) |
		(unsigned char)data->field[ft_fix(index + 3)];
	if (comd == 14)
		src->carry = (src->reg[src->arg[3]] == 0) ? 1 : 0;
}

void	ft_ldi_lldi_1(t_corewar *data, t_carriage *src, char op, char comd)
{
	int index;

	if (op == 100 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER &&
		src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
	{
		index = src->reg[src->arg[1]] + src->arg[2];
		ft_get_data(data, src, index, comd);
	}
	else if (op == 84 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER &&
		src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER && src->arg[2] >= 0 &&
		src->arg[2] <= REG_NUMBER)
	{
		index = src->reg[src->arg[1]] + src->reg[src->arg[2]];
		ft_get_data(data, src, index, comd);
	}
}

void	ft_ldi_lldi_2(t_corewar *data, t_carriage *src, char op, char comd)
{
	int index;

	if (op == -92 && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
	{
		index = src->arg[1] + src->arg[2];
		ft_get_data(data, src, index, comd);
	}
	else if (op == -108 && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER &&
		src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
	{
		index = src->arg[1] + src->reg[src->arg[2]];
		ft_get_data(data, src, index, comd);
	}
}

void	ft_ldi_lldi_3(t_corewar *data, t_carriage *src, char op, char comd)
{
	int index;

	if (op == -44 && src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER &&
		src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
	{
		index = (short)((unsigned char)data->field[ft_fix(
			src->arg[1])] << 8) | (unsigned char)data->field[
			ft_fix(src->arg[1] + 1)];
		index += src->reg[src->arg[2]];
		ft_get_data(data, src, index, comd);
	}
	else if (op == -28 && src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
	{
		index = (short)((unsigned char)data->field[ft_fix(
			src->arg[1])] << 8) | (unsigned char)data->field[
			ft_fix(src->arg[1] + 1)];
		index += src->arg[2];
		ft_get_data(data, src, index, comd);
	}
}

void	ft_ldi_lldi(t_corewar *data, t_carriage *s)
{
	char	comd;
	char	p;

	comd = data->field[s->position];
	p = data->field[ft_fix(s->position + 1)];
	if (p == 100 || p == 84 || p == -92 || p == -108 || p == -44 || p == -28)
		ft_take_arg(data, s, 0, comd);
	if (p == 100 || p == 84)
		ft_ldi_lldi_1(data, s, p, comd);
	else if (p == -92 || p == -108)
		ft_ldi_lldi_2(data, s, p, comd);
	else if (p == -44 || p == -28)
		ft_ldi_lldi_3(data, s, p, comd);
	else
		ft_inc_index(s);
	ft_bzero(s->arg, 16);
}

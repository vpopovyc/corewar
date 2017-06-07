/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:38:41 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/06 15:42:27 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

static void		ft_sti_1(t_corewar *data, t_carriage *src, char op_code, int i)
{
	if (op_code == 88 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER &&
		src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER)
	{
		i += (src->reg[src->arg[2]] + src->arg[3]) % IDX_MOD;
		data->field[ft_fix(i)] = (unsigned int)src->reg[src->arg[1]] >> 24;
		data->field[ft_fix(i + 1)] = (unsigned int)src->reg[src->arg[1]] >> 16;
		data->field[ft_fix(i + 2)] = (unsigned int)src->reg[src->arg[1]] >> 8;
		data->field[ft_fix(i + 3)] = (unsigned int)src->reg[src->arg[1]];
		ft_write_meta(data, src->name, i);
		dk_field_meta(data->meta_bold, -50, i, 4);
	}
	else if (op_code == 84 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER &&
		src->arg[2] >= 0 && src->arg[2] <= REG_NUMBER && src->arg[3] >= 0 &&
		src->arg[3] <= REG_NUMBER)
	{
		i += (src->reg[src->arg[2]] + src->reg[src->arg[3]]) % IDX_MOD;
		data->field[ft_fix(i)] = (unsigned int)src->reg[src->arg[1]] >> 24;
		data->field[ft_fix(i + 1)] = (unsigned int)src->reg[src->arg[1]] >> 16;
		data->field[ft_fix(i + 2)] = (unsigned int)src->reg[src->arg[1]] >> 8;
		data->field[ft_fix(i + 3)] = (unsigned int)src->reg[src->arg[1]];
		ft_write_meta(data, src->name, i);
		dk_field_meta(data->meta_bold, -50, i, 4);
	}
}

static void		ft_sti_2(t_corewar *data, t_carriage *src, char op_code, int i)
{
	if (op_code == 104 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
	{
		i += (src->arg[2] + src->arg[3]) % IDX_MOD;
		data->field[ft_fix(i)] = (unsigned int)src->reg[src->arg[1]] >> 24;
		data->field[ft_fix(i + 1)] = (unsigned int)src->reg[src->arg[1]] >> 16;
		data->field[ft_fix(i + 2)] = (unsigned int)src->reg[src->arg[1]] >> 8;
		data->field[ft_fix(i + 3)] = (unsigned int)src->reg[src->arg[1]];
		ft_write_meta(data, src->name, i);
		dk_field_meta(data->meta_bold, -50, i, 4);
	}
	else if (op_code == 100 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER &&
		src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
	{
		i += (src->arg[2] + src->reg[src->arg[3]]) % IDX_MOD;
		data->field[ft_fix(i)] = (unsigned int)src->reg[src->arg[1]] >> 24;
		data->field[ft_fix(i + 1)] = (unsigned int)src->reg[src->arg[1]] >> 16;
		data->field[ft_fix(i + 2)] = (unsigned int)src->reg[src->arg[1]] >> 8;
		data->field[ft_fix(i + 3)] = (unsigned int)src->reg[src->arg[1]];
		ft_write_meta(data, src->name, i);
		dk_field_meta(data->meta_bold, -50, i, 4);
	}
}

static void		ft_sti_3(t_corewar *data, t_carriage *src, char op_code, int i)
{
	if (op_code == 120 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER)
	{
		src->arg[2] = ft_take_ind(data, src->arg[2] % IDX_MOD);
		i += (src->arg[2] + src->arg[3]) % IDX_MOD;
		data->field[ft_fix(i)] = (unsigned int)src->reg[src->arg[1]] >> 24;
		data->field[ft_fix(i + 1)] = (unsigned int)src->reg[src->arg[1]] >> 16;
		data->field[ft_fix(i + 2)] = (unsigned int)src->reg[src->arg[1]] >> 8;
		data->field[ft_fix(i + 3)] = (unsigned int)src->reg[src->arg[1]];
		ft_write_meta(data, src->name, i);
		dk_field_meta(data->meta_bold, -50, i, 4);
	}
	else if (op_code == 116 && src->arg[1] >= 0 && src->arg[1] <= REG_NUMBER &&
		src->arg[3] >= 0 && src->arg[3] <= REG_NUMBER)
	{
		src->arg[2] = ft_take_ind(data, src->arg[2] % IDX_MOD);
			i += (src->arg[2] + src->reg[src->arg[3]]) % IDX_MOD;		
		data->field[ft_fix(i)] = (unsigned int)src->reg[src->arg[1]] >> 24;
		data->field[ft_fix(i + 1)] = (unsigned int)src->reg[src->arg[1]] >> 16;
		data->field[ft_fix(i + 2)] = (unsigned int)src->reg[src->arg[1]] >> 8;
		data->field[ft_fix(i + 3)] = (unsigned int)src->reg[src->arg[1]];
		ft_write_meta(data, src->name, i);
		dk_field_meta(data->meta_bold, -50, i, 4);
	}
}

void			ft_sti(t_corewar *data, t_carriage *src)
{
	char	op_code;
	int		i;

	op_code = data->field[src->position + 1];
	i = src->position;
	if (op_code == 88 || op_code == 84 || op_code == 104 || op_code == 100 ||
			op_code == 120 || op_code == 116)
		ft_take_arg(data, src, 0, data->field[src->position + 1]);
	if (op_code == 88 || op_code == 84)
		ft_sti_1(data, src, op_code, i);
	else if (op_code == 104 || op_code == 100)
		ft_sti_2(data, src, op_code, i);
	else if (op_code == 120 || op_code == 116)
		ft_sti_3(data, src, op_code, i);
	else
		ft_inc_index(src);
	ft_bzero(src->arg, 16);
}

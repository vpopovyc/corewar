/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comand_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 12:35:03 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/03 12:37:18 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_take_arg_2(t_corewar *data, t_carriage *src, int f)
{
	int res;

	res = 0;
	if (f == 2)
		res = (short)((unsigned char)data->field[ft_inc_index(src)] << 8) |
			(unsigned char)data->field[ft_inc_index(src)];
	else
		res = ((unsigned char)data->field[ft_inc_index(src)] << 24) |
			((unsigned char)data->field[ft_inc_index(src)] << 16) |
			((unsigned char)data->field[ft_inc_index(src)] << 8) |
			(unsigned char)data->field[ft_inc_index(src)];
	return (res);
}

void	ft_take_arg(t_corewar *data, t_carriage *src, int i, int comand)
{
	comand = data->field[src->position];
	ft_inc_index(src);
	src->arg[0] = data->field[src->position];
	src->arg[1] = (unsigned char)data->field[src->position] >> 6;
	src->arg[2] = (unsigned char)data->field[src->position] << 2;
	src->arg[2] = (unsigned char)src->arg[2] >> 6;
	src->arg[3] = (unsigned char)data->field[src->position] << 4;
	src->arg[3] = (unsigned char)src->arg[3] >> 6;
	ft_inc_index(src);
	while (++i < 4)
	{
		if (src->arg[i] == REG_CODE)
			src->arg[i] = data->field[ft_inc_index(src)];
		else if (src->arg[i] == DIR_CODE)
		{
			if (comand == 2 || comand == 6 || comand == 7 || comand == 8 ||
					comand == 13)
				src->arg[i] = ft_take_arg_2(data, src, 4);
			else
				src->arg[i] = ft_take_arg_2(data, src, 2);
		}
		else if (src->arg[i] == IND_CODE)
			src->arg[i] = ft_take_arg_2(data, src, 2);
	}
}

int		ft_inc_index(t_carriage *src)
{
	int res;

	res = src->position;
	if ((src->position + 1) == MEM_SIZE)
		src->position = 0;
	else
		src->position++;
	return (res);
}

int		ft_fix(int index)
{
	int res;

	if (index < 0)
	{
		while (index < 0)
			index += MEM_SIZE;
		res = index;
	}
	else if (index >= MEM_SIZE)
		res = index % MEM_SIZE;
	else
		res = index;
	return (res);
}

void	ft_write_meta(t_corewar *src, char name, int position)
{
	src->meta_data[ft_fix(position)] = name;
	src->meta_data[ft_fix(position + 1)] = name;
	src->meta_data[ft_fix(position + 2)] = name;
	src->meta_data[ft_fix(position + 3)] = name;
}

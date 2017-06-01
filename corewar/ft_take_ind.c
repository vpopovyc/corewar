/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_ind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 15:28:16 by mkrutik           #+#    #+#             */
/*   Updated: 2017/06/01 15:47:25 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_take_ind(t_corewar *data, int index)
{
	int res;

	res = ((unsigned char)data->field[ft_fix(index)] << 24) |
		((unsigned char)data->field[ft_fix(index + 1)] << 16) |
		((unsigned char)data->field[ft_fix(index +2)] << 8) |
		(unsigned char)data->field[ft_fix(index +3)];
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 17:41:00 by rvolovik          #+#    #+#             */
/*   Updated: 2017/06/01 15:48:00 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

int		count_bytes(char byte, char com_ind)
{
	if ((byte | T_REG) == T_REG)
		return (1);
	else if ((byte | T_IND) == T_IND)
		return (2);
	else if ((byte | T_DIR) == T_DIR)
	{
		if (!g_op[(int)com_ind].label_size)
			return (T_DIR * 2);
		else
			return (T_DIR);
	}
	return (0);
}

int		write_to_int(char *file, unsigned int *pos)
{
	unsigned int	ret;
	unsigned int	tmp;
	char			i;

	ret = 0;
	i = (char)sizeof(unsigned int);
	while (i)
	{
		tmp = (unsigned char)file[(*pos)++];
		ret |= tmp << (8 * (i - 1));
		--i;
	}
	return ((int)ret);
}

int		write_to_short(char *file, unsigned int *pos)
{
	unsigned int	ret;
	unsigned int	tmp;
	char			i;

	ret = 0;
	i = (char)sizeof(short);
	while (i)
	{
		tmp = (unsigned char)file[(*pos)++];
		ret |= tmp << (8 * (i - 1));
		--i;
	}
	return ((int)ret);
}

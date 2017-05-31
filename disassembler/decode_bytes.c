/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 17:41:00 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/31 20:42:54 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

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

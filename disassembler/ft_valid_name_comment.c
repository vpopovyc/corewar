/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_name_comment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 17:52:35 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/31 17:52:36 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

void	ft_take_name(t_desasm *data, char *tmp, char *p, unsigned int alignt)
{
	p = data->file_data + data->curent_position;
	tmp = ft_strnew(PROG_NAME_LENGTH);
	ft_strncpy(tmp, p, PROG_NAME_LENGTH);
	data->name = ft_strdup(tmp);
	alignt = PROG_NAME_LENGTH + 1;
	while (alignt % 4 != 0)
		alignt++;
	data->curent_position += alignt;
	ft_strdel(&tmp);
}

void	ft_valid_name_comment(t_desasm *data)
{
	char			*tmp;
	char			*p;
	unsigned int	alignt;

	ft_take_name(data, tmp, p, alignt);
	data->len_comands_code = (data->file_data[data->curent_position] << 24) |
						(data->file_data[data->curent_position + 1] << 16) |
						(data->file_data[data->curent_position + 2] << 8) |
						data->file_data[data->curent_position + 3];
	data->curent_position += 4;
	p = data->file_data + data->curent_position;
	tmp = ft_strnew(COMMENT_LENGTH);
	ft_strncpy(tmp, p, COMMENT_LENGTH);
	data->comment = ft_strdup(tmp);
	ft_strdel(&tmp);
	alignt = COMMENT_LENGTH + 1;
	while (alignt % 4 != 0)
		alignt++;
	data->curent_position += alignt;
}

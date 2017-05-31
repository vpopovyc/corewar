/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file_and_write.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 17:42:55 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/31 18:06:22 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

void	ft_create_file(t_desasm *data)
{
	char *tmp;

	tmp = ft_strjoin(data->file_name, ".s");
	ft_putstr("File ");
	ft_putstr(tmp);
	ft_putstr(" was created\n");
	data->fd = open(tmp, O_CREAT, S_IRWXU);
	close(data->fd);
	data->fd = open(tmp, O_WRONLY | O_TRUNC);
	ft_strdel(&tmp);
}

void	ft_write_comands(t_desasm *data)
{
	t_comand	*point;
	int			i;

	point = data->comands_list;
	while (point)
	{
		write(data->fd, "\t", 1);
		write(data->fd, g_op[point->name].name,
			ft_strlen(g_op[point->name].name));
		write(data->fd, "\t", 1);
		i = 0;
		while (point->arg[i])
		{
			write(data->fd, point->arg[i], ft_strlen(point->arg[i]));
			i++;
			if (point->arg[i])
				write(data->fd, ",", 1);
		}
		write(data->fd, "\n", 1);
		point = point->next;
	}
}

void	ft_create_file_and_write(t_desasm *data)
{
	char	*tmp;

	ft_create_file(data);
	write(data->fd, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING));
	tmp = ft_strjoin(" \"", data->name);
	ft_strdel(&data->name);
	data->name = ft_strjoin(tmp, "\"\n");
	write(data->fd, data->name, ft_strlen(data->name));
	ft_strdel(&tmp);
	write(data->fd, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING));
	tmp = ft_strjoin(" \"", data->comment);
	ft_strdel(&data->comment);
	data->comment = ft_strjoin(tmp, "\"\n");
	write(data->fd, data->comment, ft_strlen(data->comment));
	ft_strdel(&tmp);
	ft_write_comands(data);
	close(data->fd);
}

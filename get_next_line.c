/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 12:13:59 by mkrutik           #+#    #+#             */
/*   Updated: 2017/01/13 11:25:34 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

long	ft_read(int fd, char **src)
{
	long	len;
	char	*res;
	char	tmp[BUFF_SIZE + 1];

	ft_bzero(tmp, BUFF_SIZE + 1);
	len = read(fd, tmp, BUFF_SIZE);
	if (*src && len > 0)
	{
		res = ft_strjoin(*src, tmp);
		ft_strdel(src);
		*src = res;
	}
	else if (*src == NULL && len > 0)
		*src = ft_strdup(tmp);
	return (len);
}

int		ft_find_line(char **src, char **line, unsigned int index)
{
	char *tmp;

	tmp = *src;
	if (tmp[index] != '\0')
	{
		if (index == 0)
			*line = ft_strncpy(ft_strnew(0), tmp, index);
		else
			*line = ft_strsub(*src, 0, index);
		tmp = ft_strsub(*src, (index + 1), (ft_strlen(*src) - index - 1));
		ft_strdel(src);
		*src = tmp;
	}
	else
	{
		*line = ft_strdup(*src);
		ft_strdel(src);
	}
	return (1);
}

int		ft_get_line(char **src, int fd, char **line)
{
	char			*tmp;
	long			len_read;
	unsigned int	index;

	len_read = 1;
	if (*src == NULL)
		len_read = ft_read(fd, src);
	while (len_read != -1)
	{
		tmp = *src;
		if ((tmp == NULL || tmp[0] == '\0') && len_read == 0)
			return (0);
		index = 0;
		while (tmp[index])
		{
			if (tmp[index] == '\n')
				return (ft_find_line(src, line, index));
			else if (tmp[index + 1] == '\0' && len_read == 0)
				return (ft_find_line(src, line, (index + 1)));
			index++;
		}
		len_read = ft_read(fd, src);
	}
	return (-1);
}

int		get_next_line(const int fd, char **line)
{
	static t_file	*list;
	t_file			*point;

	if (BUFF_SIZE <= 0 || fd < 0 || !line)
		return (-1);
	point = list;
	while (point)
	{
		if (point->fd == fd)
			return (ft_get_line(&point->line, point->fd, line));
		point = point->next;
	}
	if (!(point = (t_file*)malloc(sizeof(t_file))))
		return (-1);
	point->fd = fd;
	point->line = NULL;
	point->next = list;
	list = point;
	return (ft_get_line(&point->line, point->fd, line));
}

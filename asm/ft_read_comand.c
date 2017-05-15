/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 12:05:48 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/15 12:06:05 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

char		*ft_find_label(char *src)
{
	char	*res;
	int		i;

	res = NULL;
	if (src[ft_strlen(src) - 1] == LABEL_CHAR)
	{
		i = 0;
		while (src[i] != ':')
		{
			if (!(ft_strchr(LABEL_CHARS, src[i])))
				ft_error(9);
			i++;
		}
		res = ft_strsub(src, 0, ft_strlen(src) - 1);
	}
	return (res);
}

char		*ft_find_check_comand(char *src)
{
	char	*res;

	res = NULL;
	(!(ft_strcmp(src, LIVE))) ? (res = src) : 0;
	(!(ft_strcmp(src, LD))) ? (res = src) : 0;
	(!(ft_strcmp(src, ST))) ? (res = src) : 0;
	(!(ft_strcmp(src, ADD))) ? (res = src) : 0;
	(!(ft_strcmp(src, SUB))) ? (res = src) : 0;
	(!(ft_strcmp(src, AND))) ? (res = src) : 0;
	(!(ft_strcmp(src, OR))) ? (res = src) : 0;
	(!(ft_strcmp(src, XOR))) ? (res = src) : 0;
	(!(ft_strcmp(src, ZJMP))) ? (res = src) : 0;
	(!(ft_strcmp(src, LDI))) ? (res = src) : 0;
	(!(ft_strcmp(src, STI))) ? (res = src) : 0;
	(!(ft_strcmp(src, FORK))) ? (res = src) : 0;
	(!(ft_strcmp(src, LLD))) ? (res = src) : 0;
	(!(ft_strcmp(src, LLDI))) ? (res = src) : 0;
	(!(ft_strcmp(src, LFORK))) ? (res = src) : 0;
	(!(ft_strcmp(src, AFF))) ? (res = src) : 0;
	(res == NULL) ? ft_error(10) : 0;
	return (res);
}

t_label		*ft_parse(t_label *p, char **line, t_comand *comand, char *tmp)
{
	int i;

	i = 0;
	if (i == 0 && line[i])
	{
		if ((tmp = ft_find_label(line[i])))
		{
			(p->name) ? (p->next = ft_add_label()) : 0;
			(p->name) ? (p->next->comand = ft_add_comand()) : 0;
			(p->name) ? (p = p->next) : 0;
			p->name = tmp;
			i++;
		}
		else if (!p->name)
			p->name = ft_strdup("empty");
	}
	if (!line[i])
		return (p);
	(!line[i] || !(tmp = ft_find_check_comand(line[i++]))) ? ft_error(10) : 0;
	comand = (p->comand->name) ? ft_end(p->comand) : ft_current(p->comand);
	comand->name = ft_strdup(tmp);
	ft_find_arguments(comand, line, i, 0);
	ft_free_two_dimensional_array(line);
	return (p);
}

void		ft_write_comands(t_gamer *src, char *tmp, int f, char **line)
{
	t_label		*point;
	t_comand	*comand;

	comand = NULL;
	point = src->label;
	while (get_next_line(src->fd, &tmp) > 0)
	{
		(!tmp || tmp[0] == '\0') ? (f = 1) : 0;
		if (tmp && tmp[0] != '\0')
		{
			line = all_delims_split(tmp);
			f = (!line) ? 1 : 0;
			if (line)
			{
				(!ft_strcmp(line[0], NAME_CMD_STRING) || !ft_strcmp(line[0],
							COMMENT_CMD_STRING)) ? ft_error(6) : 0;
				(line[0][0] == COMMENT_CHAR) ?
					ft_free_two_dimensional_array(line) :
					(point = ft_parse(point, line, comand, NULL));
			}
		}
		free(tmp);
	}
	(f == 0) ? ft_error(12) : 0;
}

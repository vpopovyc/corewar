/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validation_head.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <mkrutik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:07:23 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/08 15:56:30 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

void	ft_check_len(t_gamer *data)
{
	if (ft_strlen(data->name) > PROG_NAME_LENGTH)
		ft_error(7);
	if (ft_strlen(data->comment) > COMMENT_LENGTH)
		ft_error(8);
	ft_bzero(data->src->prog_name, PROG_NAME_LENGTH);
	ft_bzero(data->src->comment, COMMENT_LENGTH);
	ft_strcpy(data->src->prog_name, data->name);
	ft_strcpy(data->src->comment, data->comment);
	data->src->magic = COREWAR_EXEC_MAGIC;
}

void	ft_next_line(t_gamer *src, int dest, int b, unsigned int len)
{
	char			*dump;
	char			*del;
	char			*tmp;
	unsigned int	index;

	while (b == 0 && get_next_line(src->fd, &tmp) > 0)
	{
		index = -1;
		len = 0;
		while (tmp[++index] && tmp[index] != '"')
			len++;
		(tmp[index] == '"') ? (b = 1) : 0;
		del = (len != 0) ? ft_strsub(tmp, index - len, len) : ft_strdup("");
		dump = ft_strjoin("\n", del);
		free(del);
		del = (dest == 0) ? src->name : src->comment;
		(dest == 0) ? (src->name = ft_strjoin(src->name, dump)) :
			(src->comment = ft_strjoin(src->comment, dump));
		free(del);
		free(dump);
		(b == 0) ? free(tmp) : 0;
	}
	(b != 1) ? ft_error(6) : 0;
	while (tmp[++index])
		(ft_isspace(tmp[index])) ? (index++) : ft_error(6);
}

void	ft_name(t_gamer *src, char *tmp, unsigned int index, unsigned int len)
{
	index = src->len_def_name;
	while (ft_isspace(tmp[index]))
		index++;
	(tmp[index++] != '"') ? ft_error(6) : 0;
	if (tmp[index] == '"')
		src->name = ft_strdup("");
	else
	{
		len = 0;
		while (tmp[index] && tmp[index] != '"')
		{
			index++;
			len++;
		}
		src->name = ft_strsub(tmp, index - len, len);
		(tmp[index] != '"') ? ft_next_line(src, 0, 0, 0) : (index++);
	}
	while (tmp[index])
	{
		if (!ft_isspace(tmp[index]))
			ft_error(6);
		index++;
	}
	free(tmp);
	src->header++;
}

void	ft_comment(t_gamer *src, char *tmp, unsigned int i, unsigned int len)
{
	(src->name == NULL) ? ft_error(6) : 0;
	i = src->len_def_comment;
	while (ft_isspace(tmp[i]))
		i++;
	(tmp[i++] != '"') ? ft_error(6) : 0;
	len = 0;
	while (tmp[i] && tmp[i] != '"')
	{
		i++;
		len++;
	}
	src->comment = ft_strsub(tmp, i - len, len);
	(tmp[i] != '"') ? ft_next_line(src, 1, 0, 0) : (i++);
	while (tmp[i])
	{
		if (!ft_isspace(tmp[i]))
			ft_error(6);
		i++;
	}
	free(tmp);
	src->header++;
}

void	ft_validation(t_gamer *new)
{
	char	*tmp;
	char	*del;

	new->len_def_name = (unsigned int)ft_strlen(NAME_CMD_STRING);
	new->len_def_comment = (unsigned int)ft_strlen(COMMENT_CMD_STRING);
	while (new->header != 2 && get_next_line(new->fd, &tmp) > 0)
	{
		del = tmp;
		while (ft_isspace(*tmp))
			tmp++;
		if (!(ft_strncmp(tmp, NAME_CMD_STRING, new->len_def_name)))
			ft_name(new, ft_strdup(tmp), 0, 0);
		else if (!(ft_strncmp(tmp, COMMENT_CMD_STRING, new->len_def_comment)))
			ft_comment(new, ft_strdup(tmp), 0, 0);
		else if (*tmp != COMMENT_CHAR && *tmp != '\0')
			ft_error(6);
		free(del);
	}
	if (new->header != 2)
		ft_error(6);
	ft_check_len(new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 20:35:55 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/22 20:35:57 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/byte_code_header.h"

static void		check_header_mems_len(int len)
{
	if (len == PROG_NAME_LENGTH)
		ft_error(7, g_line);
	else if (len == COMMENT_LENGTH)
		ft_error(8, g_line);
}

static void		next_line(char *dest, int len)
{
	char	*quote;
	char	*tmp;

	while (get_next_line(g_fd_s, &tmp) > 0 && !(quote = ft_strchr(tmp, QUOTE)))
	{
		++g_line;
		dest[ft_strlen(dest)] = '\n';
		if ((int)(ft_strlen(dest) + ft_strlen(tmp)) <= len)
			ft_strncpy(dest + ft_strlen(dest), tmp, ft_strlen(tmp));
		else
			check_header_mems_len(len);
		free(tmp);
	}
	dest[ft_strlen(dest)] = '\n';
	if ((int)(ft_strlen(dest) + ft_strlen(tmp) - 1) <= len)
		ft_strncpy(dest + ft_strlen(dest), tmp, quote - tmp);
	else
		check_header_mems_len(len);
	while (*(quote + 1))
	{
		if (!ft_isspace(*(quote + 1)))
			ft_error(6, g_line);
		quote++;
	}
	free(tmp);
}

static void		get_string(char *src, char *dest, int len)
{
	char	*start;
	char	*quote;

	if (!(start = ft_strchr(src, QUOTE)))
		ft_error(6, g_line);
	if ((quote = ft_strchr(start + 1, QUOTE)) && quote - start - 1 <= len)
	{
		ft_strncpy(dest, start + 1, quote - start - 1);
		while (*(quote + 1))
		{
			if (!isspace(*(quote + 1)))
				ft_error(6, g_line);
			quote++;
		}
	}
	else if (!quote)
	{
		ft_strncpy(dest, start + 1, ft_strlen(start + 1));
		next_line(dest, len);
	}
	else
		check_header_mems_len(len);
}

static void		ft_validation(t_base *new)
{
	char	*tmp;
	char	*del;
	int		header;

	header = 0;
	while (header != HEADER_PARTS && get_next_line(g_fd_s, &tmp) > 0)
	{
		++g_line;
		del = tmp;
		skip_spaces(&tmp);
		if (ft_strnequ(tmp, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))
				&& ++header)
			get_string(tmp, new->reference->comment, COMMENT_LENGTH);
		else if (ft_strnequ(tmp, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))
				&& ++header)
			get_string(tmp, new->reference->prog_name, PROG_NAME_LENGTH);
		else if (*tmp != COMMENT_CHAR && *tmp != '\0')
			ft_error(6, g_line);
		free(del);
	}
	if (header != HEADER_PARTS)
		ft_error(6, g_line);
	new->reference->magic = COREWAR_EXEC_MAGIC;
}

t_base			*init_validation(char *av)
{
	t_base *new;

	g_line = 0;
	new = (t_base*)ft_memalloc(sizeof(t_base));
	new->reference = (header_t*)ft_memalloc(sizeof(header_t));
	new->table = (t_hash*)ft_memalloc(sizeof(t_hash) * SIZEOFTABLE);
	stack_init(&(new->q_label));
	new->path = ft_open(av);
	ft_validation(new);
	return (new);
}

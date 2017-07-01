/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 09:32:43 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/19 09:32:53 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_valid_magic(char *point)
{
	unsigned int	magic;

	magic = 0;
	magic = (unsigned char)point[0] << 24 | (unsigned char)point[1] << 16 |
		(unsigned char)point[2] << 8 | (unsigned char)point[3];
	if (magic != COREWAR_EXEC_MAGIC)
		ft_error(11);
	ft_bzero(point, 4);
}

char		*ft_n_or_c(char *src, size_t n_byts)
{
	size_t	len;
	char	*res;

	len = ft_strlen(src);
	while (len < n_byts)
		(src[len] != '\0') ? ft_error(5) : (len++);
	res = ft_strdup(src);
	ft_bzero(src, n_byts);
	return (res);
}

void		ft_valid_size(char *src, t_player *res)
{
	unsigned int	size;

	size = 0;
	size = (unsigned char)src[0] << 24 | (unsigned char)src[1] << 16 |
		(unsigned char)src[2] << 8 | (unsigned char)src[3];
	res->size = size;
	ft_bzero(src, 4);
}

void		ft_valid_code(char *src, t_player *res)
{
	(src[0] == '\0') ? ft_error(5) : 0;
	res->code = ft_strnew(res->size);
	ft_memcpy(res->code, src, res->size);
	ft_bzero(src, res->size);
}

t_player	*ft_valid_cor(int fd, size_t len, size_t r)
{
	t_player	*new;
	char		tmp[PROG_NAME_LENGTH + CHAMP_MAX_SIZE + 9 + COMMENT_LENGTH];

	new = (t_player*)malloc(sizeof(t_player));
	(read(fd, tmp, 0) < 0) ? ft_error(10) : 0;
	((r = read(fd, tmp, 4)) != 4) ? ft_error(5) : ft_valid_magic(tmp);
	len = PROG_NAME_LENGTH + 1;
	while ((len % 4) != 0)
		len++;
	((r = read(fd, tmp, len)) != len) ? ft_error(5) :
		(new->name = ft_n_or_c(tmp, len));
	((r = read(fd, tmp, 4)) != 4) ? ft_error(5) : ft_valid_size(tmp, new);
	len = COMMENT_LENGTH + 1;
	while ((len % 4) != 0)
		len++;
	((r = read(fd, tmp, len)) != len) ? ft_error(5) :
		(new->comment = ft_n_or_c(tmp, len));
	((r = read(fd, tmp, new->size)) != new->size) ? ft_error(5) :
		ft_valid_code(tmp, new);
	((r = read(fd, tmp, 10)) != 0 || new->size > CHAMP_MAX_SIZE) ?
		ft_error(5) : 0;
	new->next = NULL;
	return (new);
}

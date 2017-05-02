/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 12:15:34 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/02 16:31:33 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10000
# include "libft/libft.h"
# include <fcntl.h>

typedef struct		s_file
{
	int				fd;
	char			*line;
	struct s_file	*next;
}					t_file;

int					get_next_line(const int fd, char **line);
#endif

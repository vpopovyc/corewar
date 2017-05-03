/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:42:55 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/03 16:10:03 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "../libft/includes/libft.h"
# include "../op.h"

typedef struct		s_gamer
{
	header_t		*src;
	char			*name;
	char			*comment;
	int				header;
	int				fd;
	unsigned int	len_def_name;
	unsigned int	len_def_comment;
}					t_gamer;

void				ft_error(int n);
void				ft_validation(t_gamer *src);
int					ft_isspace(char c);
#endif

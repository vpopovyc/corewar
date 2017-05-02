/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:42:55 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/02 17:22:00 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "../libft/libft.h"
# include "../get_next_line.h"

typedef struct	s_gamer
{
	char		*name;
	char		*comment;
	int			header;
	int			fd;
}				t_gamer;

//void	ft_error(int n);

#endif

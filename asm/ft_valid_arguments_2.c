/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_arguments_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 12:15:02 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/15 12:15:23 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

int		ft_arg(t_comand *src, char **arguments, int index, int *n_arg)
{
	int		j;
	char	*tmp;

	j = 0;
	while (arguments[j])
	{
		n_arg[index] = ft_valid_comand_arguments(arguments[j++], &tmp);
		(index == 0) ? (src->arg1 = tmp) : 0;
		(index == 1) ? (src->arg2 = tmp) : 0;
		(index++ == 2) ? (src->arg3 = tmp) : 0;
	}
	return (index);
}

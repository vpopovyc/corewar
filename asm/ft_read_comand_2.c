/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_comand_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 11:44:35 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/12 11:46:11 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

void		ft_free_two_dimensional_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_strdel(&array[i]);
		i++;
	}
	free(array);
}

t_comand	*ft_current(t_comand *src)
{
	t_comand	*res;

	res = src;
	while (res->next)
		res = res->next;
	return (res);
}

t_comand	*ft_end(t_comand *src)
{
	t_comand	*new;

	new = src;
	while (new->next)
		new = new->next;
	new->next = ft_add_comand();
	new = new->next;
	return (new);
}

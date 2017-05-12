/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_comand_struct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 11:20:45 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/12 11:20:54 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

t_comand	*ft_add_comand(void)
{
	t_comand *new;

	(!(new = (t_comand*)malloc(sizeof(t_comand)))) ? ft_error(1) : 0;
	new->name = NULL;
	new->arg1 = NULL;
	new->arg2 = NULL;
	new->arg3 = NULL;
	new->hex_code = 0;
	new->next = NULL;
	return (new);
}

t_label		*ft_add_label(void)
{
	t_label	*new;

	(!(new = (t_label*)malloc(sizeof(t_label)))) ? ft_error(1) : 0;
	new->name = NULL;
	new->comand = NULL;
	new->next = NULL;
	return (new);
}

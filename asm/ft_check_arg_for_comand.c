/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_for_comand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 12:17:37 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/15 12:17:42 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

void	ft_check_for_comand(char *n, int op)
{
	if (!ft_strcmp(n, LIVE) || !ft_strcmp(n, ZJMP) || !ft_strcmp(n, LFORK) ||
		!ft_strcmp(n, AFF) || !ft_strcmp(n, FORK))
		(op != -128) ? ft_error(11) : 0;
	else if (!ft_strcmp(n, LD))
		(op != -48 && op != -112) ? ft_error(11) : 0;
	else if (!ft_strcmp(n, ST))
		(op != 112 && op != 80) ? ft_error(11) : 0;
	else if (!ft_strcmp(n, ADD) || !ft_strcmp(n, SUB))
		(op != 84) ? ft_error(11) : 0;
	else if (!ft_strcmp(n, AND) || !ft_strcmp(n, OR) || !ft_strcmp(n, XOR))
		(op != 84 && op != 100 && op != 116 && op != -108 && op != -92 && op
		!= -76 && op != -44 && op != -12 && op != -28) ? ft_error(11) : 0;
	else if (!ft_strcmp(n, LDI))
		(op != 100 && op != 84 && op != -92 && op != -108 && op != -28 && op
		!= -44) ? ft_error(11) : 0;
	else if (!ft_strcmp(n, STI))
		(op != 88 && op != 84 && op != 104 && op != 100 && op != 120 &&
		op != 116) ? ft_error(11) : 0;
	else if (!ft_strcmp(n, LLD))
		(op != -112 && op != -48) ? ft_error(11) : 0;
	else if (!ft_strcmp(n, LLDI))
		(op != 100 && op != 84 && op != -92 && op != -108 && op != -28 && op
		!= -44) ? ft_error(11) : 0;
}

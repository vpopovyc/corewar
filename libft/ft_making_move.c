/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_making_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 14:11:32 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/06 14:55:20 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void			ft_group_other_sign(t_printf **pf)
{
	(*pf)->sm == 3 ? (*pf)->sm = 0 : 0;
	(*pf)->ltx = 1;
	(*pf)->hex = 42;
}

void			ft_string_sign(t_printf **pf)
{
	ssize_t		i;
	ssize_t		b;

	if ((*pf)->tx == NULL)
		(*pf)->tx = "(null)";
	b = (ssize_t)ft_strlen((*pf)->tx);
	i = ((*pf)->presc == -1) ? b : (*pf)->presc;
	(*pf)->ltx = (*((*pf)->tx) != '\0') ? (int)i : 0;
	(*((*pf)->spec + (*pf)->lspc - 1) == '.') ? (*pf)->ltx = 0 : 0;
	((*pf)->presc > b) ? (*pf)->ltx = (int)b : 0;
	(*pf)->hex = 42;
}

static	int		ft_get_arg(t_printf **pf, va_list *pc)
{
	ssize_t		i;
	ssize_t		b;

	i = (*pf)->min_field + (*pf)->nf;
	b = (*pf)->presc + (*pf)->nf;
	if (b > (*pf)->mnpr || i > (*pf)->mnpr)
	{
		(*pf)->lnpr = -1;
		return (0);
	}
	(ft_iscl_group1((*pf)->cl)) ? ft_group1(pf, pc) : 0;
	(ft_iscl_group2((*pf)->cl)) ? ft_group2(pf, pc) : 0;
	(ft_iscl_group3((*pf)->cl)) ? ft_group3(pf, pc) : 0;
	if ((*pf)->lnpr == -1)
		return (0);
	(*pf)->mnpr -= (*pf)->lnpr;
	(*pf)->nf = 0;
	return (1);
}

void			ft_making_move(t_printf **pf, va_list *pc, char *sv)
{
	while (*sv)
	{
		if (*sv == '%')
		{
			ft_s_spec(pf, sv, pc);
			(*pf)->ft = ft_strnfjoin((*pf)->ft, sv - (*pf)->nf, (*pf)->nf);
			if (!ft_get_arg(pf, pc))
				return ;
			sv += (*pf)->lspc + 1;
		}
		else
		{
			++(*pf)->nf;
			++sv;
		}
	}
	if ((*pf)->nf != 0)
	{
		(*pf)->lnpr += (*pf)->nf;
		if (ft_check(pf))
			ft_psn(sv - (*pf)->nf, (*pf)->nf);
	}
}

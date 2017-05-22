/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_group_united.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 19:50:31 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/06 14:50:24 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static	void			ft_bit_output(t_printf **pf)
{
	ft_psn((*pf)->ft, (*pf)->nf);
	if ((*pf)->cf[1] == '-')
	{
		if ((*pf)->cl == 's' && (*pf)->sm == 3)
			ft_pspp((*pf)->ws);
		else if ((*pf)->cl == 's')
			ft_psn((*pf)->tx, (*pf)->ltx);
		else
			write(1, &(*pf)->c, 1);
		ft_pssn((*pf)->field, (*pf)->fld);
	}
	else
	{
		ft_pssn((*pf)->field, (*pf)->fld);
		if (((*pf)->cl == 's') && (*pf)->sm == 3)
			ft_pspp((*pf)->ws);
		else if ((*pf)->cl == 's')
			ft_psn((*pf)->tx, (*pf)->ltx);
		else if ((*pf)->cl == 'c' && (*pf)->sm == 3)
			ft_putstr(*(*pf)->ws);
		else
			write(1, &(*pf)->c, 1);
	}
	(*pf)->lnpr += (*pf)->nf + (*pf)->ltx;
}

void					ft_group_one_output(t_printf **pf)
{
	ft_psn((*pf)->ft, (*pf)->nf);
	if ((*pf)->cf[1] == '-')
	{
		ft_psn(&(*pf)->sign, 1);
		ft_pssn((*pf)->prefix, (*pf)->prx);
		ft_psn((*pf)->tx, (*pf)->ltx);
		ft_pssn((*pf)->field, (*pf)->fld);
	}
	else
	{
		if ((*pf)->sign != '\0' && (*pf)->field == '0')
			ft_psn(&(*pf)->sign, 1);
		ft_pssn((*pf)->field, (*pf)->fld);
		if ((*pf)->sign != '\0' && (*pf)->field != '0')
			ft_psn(&(*pf)->sign, 1);
		ft_pssn((*pf)->prefix, (*pf)->prx);
		ft_psn((*pf)->tx, (*pf)->sign == '-' ? (*pf)->ltx - 1 : (*pf)->ltx);
	}
	(*pf)->lnpr += (*pf)->nf + (*pf)->ltx;
}

void					ft_group_two_output(t_printf **pf)
{
	ft_psn((*pf)->ft, (*pf)->nf);
	if ((*pf)->cf[1] == '-')
	{
		ft_psn(&(*pf)->sign, 1);
		ft_psn(&(*pf)->hex, 1);
		ft_pssn((*pf)->prefix, (*pf)->prx);
		ft_psn((*pf)->tx, (*pf)->ltx);
		ft_pssn((*pf)->field, (*pf)->fld);
	}
	else
	{
		((*pf)->sign != 0 && (*pf)->field == '0') ? ft_psn(&(*pf)->sign, 1) : 0;
		((*pf)->sign != 0 && (*pf)->field == '0') ? ft_psn(&(*pf)->hex, 1) : 0;
		ft_pssn((*pf)->field, (*pf)->fld);
		((*pf)->sign != 0 && (*pf)->field != '0') ? ft_psn(&(*pf)->sign, 1) : 0;
		((*pf)->sign != 0 && (*pf)->field != '0') ? ft_psn(&(*pf)->hex, 1) : 0;
		ft_pssn((*pf)->prefix, (*pf)->prx);
		ft_psn((*pf)->tx, (*pf)->ltx);
	}
	(*pf)->lnpr += (*pf)->nf + (*pf)->ltx;
}

void					ft_group_prefix(t_printf **pf)
{
	(*pf)->prx = (*pf)->ltx - (*pf)->presc;
	if ((*pf)->prx < 0 && (*pf)->presc != -1)
		(*pf)->prx = -(*pf)->prx;
	else
	{
		(*pf)->prx = 0;
		return ;
	}
	(*pf)->lnpr += (*pf)->prx;
	if (ft_check(pf) == -1)
		return ;
	(*pf)->prefix = '0';
}

void					ft_group_field(t_printf **pf)
{
	ft_group_prefix(pf);
	(*pf)->fld = (*pf)->ltx + (*pf)->prx - (*pf)->min_field;
	if ((*pf)->fld < 0)
		(*pf)->fld = -(*pf)->fld;
	else if ((*pf)->lnpr != -1)
	{
		if ((*pf)->hex == 42)
			return (ft_bit_output(pf));
		return ;
	}
	else
		return ;
	(*pf)->lnpr += (*pf)->fld;
	if (ft_check(pf) == -1)
		return ;
	if ((*pf)->cf[4] != '0' || (*pf)->presc >= (*pf)->ltx)
		(*pf)->field = ' ';
	else if ((*pf)->cf[1] == '-')
		(*pf)->field = ' ';
	else
		(*pf)->field = '0';
	((*pf)->hex == 42) ? ft_bit_output(pf) : 0;
}

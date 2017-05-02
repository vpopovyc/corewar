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

#include "includes/ft_fprintf.h"

static	void			ft_fbit_output(t_fprintf **pf)
{
	psn((*pf)->ft, (*pf)->nf, (*pf)->fd);
	if ((*pf)->cf[1] == '-')
	{
		if ((*pf)->cl == 's' && (*pf)->sm == 3)
			pspp((*pf)->ws, (*pf)->fd);
		else if ((*pf)->cl == 's')
			psn((*pf)->tx, (*pf)->ltx, (*pf)->fd);
		else
			write((*pf)->fd, &(*pf)->c, 1);
		pssn((*pf)->field, (*pf)->fld, (*pf)->fd);
	}
	else
	{
		pssn((*pf)->field, (*pf)->fld, (*pf)->fd);
		if (((*pf)->cl == 's') && (*pf)->sm == 3)
			pspp((*pf)->ws, (*pf)->fd);
		else if ((*pf)->cl == 's')
			psn((*pf)->tx, (*pf)->ltx, (*pf)->fd);
		else if ((*pf)->cl == 'c' && (*pf)->sm == 3)
			ft_putstr_fd(*(*pf)->ws, (*pf)->fd);
		else
			write((*pf)->fd, &(*pf)->c, 1);
	}
	(*pf)->lnpr += (*pf)->nf + (*pf)->ltx;
}

void					ft_fgroup_one_output(t_fprintf **pf)
{
	int		f;

	f = (*pf)->fd;
	psn((*pf)->ft, (*pf)->nf, f);
	if ((*pf)->cf[1] == '-')
	{
		psn(&(*pf)->sign, 1, f);
		pssn((*pf)->prefix, (*pf)->prx, f);
		psn((*pf)->tx, (*pf)->ltx, f);
		pssn((*pf)->field, (*pf)->fld, f);
	}
	else
	{
		if ((*pf)->sign != '\0' && (*pf)->field == '0')
			psn(&(*pf)->sign, 1, f);
		pssn((*pf)->field, (*pf)->fld, f);
		if ((*pf)->sign != '\0' && (*pf)->field != '0')
			psn(&(*pf)->sign, 1, f);
		pssn((*pf)->prefix, (*pf)->prx, f);
		psn((*pf)->tx, (*pf)->sign == '-' ? (*pf)->ltx - 1 : (*pf)->ltx, f);
	}
	(*pf)->lnpr += (*pf)->nf + (*pf)->ltx;
}

void					ft_fgroup_two_output(t_fprintf **pf)
{
	int		f;

	f = (*pf)->fd;
	psn((*pf)->ft, (*pf)->nf, f);
	if ((*pf)->cf[1] == '-')
	{
		psn(&(*pf)->sign, 1, f);
		psn(&(*pf)->hex, 1, f);
		pssn((*pf)->prefix, (*pf)->prx, f);
		psn((*pf)->tx, (*pf)->ltx, f);
		pssn((*pf)->field, (*pf)->fld, f);
	}
	else
	{
		((*pf)->sign != 0 && (*pf)->field == '0') ? psn(&(*pf)->sign, 1, f) : 0;
		((*pf)->sign != 0 && (*pf)->field == '0') ? psn(&(*pf)->hex, 1, f) : 0;
		pssn((*pf)->field, (*pf)->fld, f);
		((*pf)->sign != 0 && (*pf)->field != '0') ? psn(&(*pf)->sign, 1, f) : 0;
		((*pf)->sign != 0 && (*pf)->field != '0') ? psn(&(*pf)->hex, 1, f) : 0;
		pssn((*pf)->prefix, (*pf)->prx, f);
		psn((*pf)->tx, (*pf)->ltx, f);
	}
	(*pf)->lnpr += (*pf)->nf + (*pf)->ltx;
}

void					ft_fgroup_prefix(t_fprintf **pf)
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
	if (ft_fcheck(pf) == -1)
		return ;
	(*pf)->prefix = '0';
}

void					ft_fgroup_field(t_fprintf **pf)
{
	ft_fgroup_prefix(pf);
	(*pf)->fld = (*pf)->ltx + (*pf)->prx - (*pf)->min_field;
	if ((*pf)->fld < 0)
		(*pf)->fld = -(*pf)->fld;
	else if ((*pf)->lnpr != -1)
	{
		if ((*pf)->hex == 42)
			return (ft_fbit_output(pf));
		return ;
	}
	else
		return ;
	(*pf)->lnpr += (*pf)->fld;
	if (ft_fcheck(pf) == -1)
		return ;
	if ((*pf)->cf[4] != '0' || (*pf)->presc >= (*pf)->ltx)
		(*pf)->field = ' ';
	else if ((*pf)->cf[1] == '-')
		(*pf)->field = ' ';
	else
		(*pf)->field = '0';
	((*pf)->hex == 42) ? ft_fbit_output(pf) : 0;
}

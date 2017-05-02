/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 17:25:16 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/06 14:59:14 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void		ft_puppies_killa(t_printf **pf)
{
	if ((*pf)->tx != NULL)
	{
		if (ft_iscl_group3((*pf)->cl) != 1)
			free(((*pf)->sign == '-') ? (*pf)->tx - 1 : (*pf)->tx);
	}
	((*pf)->ws != NULL && *((*pf)->ws) != '\0') ? ft_ppdel(&(*pf)->ws) : 0;
	((*pf)->ft != NULL) ? ft_strdel(&(*pf)->ft) : 0;
	(*pf)->spec != NULL || *((*pf)->spec) != '0' ? ft_strdel(&(*pf)->spec) : 0;
	((*pf)->cf != NULL) ? ft_strdel(&(*pf)->cf) : 0;
	free(*pf);
}

ssize_t		ft_check(t_printf **pf)
{
	if ((*pf)->lnpr + (*pf)->nf + (*pf)->ltx > (*pf)->mnpr)
		return ((*pf)->lnpr = -1);
	return (1);
}

void		ft_s_printf_clr(t_printf **pf)
{
	((*pf)->ws != NULL) ? ft_ppdel(&(*pf)->ws) : 0;
	if ((*pf)->tx != NULL && ft_iscl_group3((*pf)->cl) != 1)
		free(((*pf)->sign == '-') ? (*pf)->tx - 1 : (*pf)->tx);
	(*pf)->cl = 0;
	(*pf)->lspc = 0;
	(*pf)->presc = -1;
	(*pf)->min_field = 0;
	(*pf)->sm = 0;
	ft_strclr((*pf)->ft);
	ft_strclr((*pf)->spec);
	ft_memset((*pf)->cf, '*', 5);
	(*pf)->ltx = 0;
	(*pf)->prefix = 0;
	(*pf)->prx = 0;
	(*pf)->field = 0;
	(*pf)->fld = 0;
	(*pf)->sign = 0;
	(*pf)->hex = 0;
	(*pf)->base = 10;
	(*pf)->c = 0;
	(*pf)->wc = NULL;
}

void		ft_norm(t_printf **new)
{
	(*new)->tx = NULL;
	(*new)->ltx = 0;
	(*new)->prefix = 0;
	(*new)->prx = 0;
	(*new)->field = 0;
	(*new)->fld = 0;
	(*new)->sign = 0;
	(*new)->hex = 0;
	(*new)->base = 10;
	(*new)->lnpr = 0;
	(*new)->wc = NULL;
	(*new)->ws = NULL;
	(*new)->c = 0;
}

t_printf	*ft_s_printf_new(void)
{
	t_printf	*new;

	new = (t_printf*)malloc(sizeof(t_printf));
	new->cl = 0;
	new->lspc = 0;
	new->presc = -1;
	new->min_field = 0;
	new->sm = 0;
	new->nf = 0;
	new->mnpr = INT_MAX;
	new->lnpr = 0;
	new->ft = ft_strnew(0);
	new->spec = ft_strnew(0);
	new->cf = ft_strnew(5);
	ft_memset(new->cf, '*', 5);
	ft_norm(&new);
	return (new);
}

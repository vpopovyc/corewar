/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit_party.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 17:28:41 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/06 15:43:38 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fprintf.h"

static char		*ft_fafter_party(wchar_t c)
{
	unsigned char	*data;

	data = (unsigned char*)malloc(sizeof(data) * 5);
	data = (unsigned char*)ft_uct8(c, data, ft_wstrblen(c));
	return ((char*)data);
}

static char		ft_fnull_party(t_fprintf **pf, wchar_t *s)
{
	if (s == NULL)
	{
		(*pf)->tx = "(null)";
		(*pf)->ltx = (int)ft_strlen((*pf)->tx);
		(*pf)->hex = 42;
		(*pf)->sm = 0;
		return (1);
	}
	return (0);
}

void			ft_fbit_party(t_fprintf **pf, wchar_t *s)
{
	int		i;
	int		tmp;

	i = 0;
	if (ft_fnull_party(pf, s))
		return ;
	tmp = ((*pf)->presc == -1) ? (int)ft_wstrmem(s) : ((*pf)->presc);
	tmp = (*((*pf)->spec + (*pf)->lspc - 1) == '.') ? 0 : tmp;
	while (s[i])
	{
		tmp -= ft_wstrblen(s[i]);
		if (tmp < 0)
			break ;
		(*pf)->ltx = (*pf)->presc - tmp;
		++i;
	}
	(*pf)->ws = (char**)malloc(sizeof(char*) * i + 1);
	*((*pf)->ws + i) = NULL;
	while (--i >= 0)
		*((*pf)->ws + i) = ft_fafter_party(s[i]);
	(*pf)->hex = 42;
	((*pf)->presc == -1) ? (*pf)->ltx = (int)ft_wstrmem(s) : 0;
	(*((*pf)->spec + (*pf)->lspc - 1) == '.') ? (*pf)->ltx = 0 : 0;
}

void			ft_fweof_camp(t_fprintf **pf, va_list *pc)
{
	wint_t		i;
	wchar_t		t;
	int			len;
	char		*tmp;

	i = va_arg(*pc, wint_t);
	if (i == -1)
	{
		(*pf)->lnpr = -1;
		return ;
	}
	if (i == '\0')
	{
		ft_fgroup_other_sign(pf);
		(*pf)->presc = -1;
		return (ft_fgroup_field(pf));
	}
	t = (wchar_t)i;
	len = ft_wstrblen(t);
	tmp = ft_fafter_party(t);
	(*pf)->lnpr += len + (*pf)->nf;
	psn((*pf)->ft, (*pf)->nf, (*pf)->fd);
	ft_putstr_fd(tmp, (*pf)->fd);
	free(tmp);
}

void			ft_fgroup3(t_fprintf **pf, va_list *pc)
{
	if ((*pf)->cl == 's' && (*pf)->sm == 3)
	{
		(*pf)->wc = va_arg(*pc, wchar_t *);
		ft_fbit_party(pf, (*pf)->wc);
	}
	else if ((*pf)->cl == 's')
	{
		(*pf)->tx = va_arg(*pc, char *);
		ft_fstring_sign(pf);
	}
	else if ((*pf)->cl == 'c' && (*pf)->sm == 3)
		return (ft_fweof_camp(pf, pc));
	else
	{
		if ((*pf)->cl == 'c')
			(*pf)->c = va_arg(*pc, int);
		else
			(*pf)->c = (*pf)->cl;
		ft_fgroup_other_sign(pf);
	}
	if ((*pf)->lnpr == -1)
		return ;
	(*pf)->presc = -1;
	ft_fgroup_field(pf);
}

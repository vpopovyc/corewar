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

#include "includes/ft_printf.h"

static char		*ft_after_party(wchar_t c)
{
	unsigned char	*data;

	data = (unsigned char*)malloc(sizeof(data) * 5);
	data = (unsigned char*)ft_uct8(c, data, ft_wstrblen(c));
	return ((char*)data);
}

static char		ft_null_party(t_printf **pf, wchar_t *s)
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

void			ft_bit_party(t_printf **pf, wchar_t *s)
{
	int		i;
	int		tmp;

	i = 0;
	if (ft_null_party(pf, s))
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
		*((*pf)->ws + i) = ft_after_party(s[i]);
	(*pf)->hex = 42;
	((*pf)->presc == -1) ? (*pf)->ltx = (int)ft_wstrmem(s) : 0;
	(*((*pf)->spec + (*pf)->lspc - 1) == '.') ? (*pf)->ltx = 0 : 0;
}

void			ft_weof_camp(t_printf **pf, va_list *pc)
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
		ft_group_other_sign(pf);
		(*pf)->presc = -1;
		return (ft_group_field(pf));
	}
	t = (wchar_t)i;
	len = ft_wstrblen(t);
	tmp = ft_after_party(t);
	(*pf)->lnpr += len + (*pf)->nf;
	ft_psn((*pf)->ft, (*pf)->nf);
	ft_putstr(tmp);
	free(tmp);
}

void			ft_group3(t_printf **pf, va_list *pc)
{
	if ((*pf)->cl == 's' && (*pf)->sm == 3)
	{
		(*pf)->wc = va_arg(*pc, wchar_t *);
		ft_bit_party(pf, (*pf)->wc);
	}
	else if ((*pf)->cl == 's')
	{
		(*pf)->tx = va_arg(*pc, char *);
		ft_string_sign(pf);
	}
	else if ((*pf)->cl == 'c' && (*pf)->sm == 3)
		return (ft_weof_camp(pf, pc));
	else
	{
		if ((*pf)->cl == 'c')
			(*pf)->c = va_arg(*pc, int);
		else
			(*pf)->c = (*pf)->cl;
		ft_group_other_sign(pf);
	}
	if ((*pf)->lnpr == -1)
		return ;
	(*pf)->presc = -1;
	ft_group_field(pf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:20:45 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/06 15:04:51 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static void		ft_flags(char *sv, t_printf **pf)
{
	char f;

	f = 1;
	while (*(++sv))
	{
		(*sv >= '1' && *sv <= '9' && f) ? f = 0 : 0;
		(*sv == '#') ? (*pf)->cf[0] = '#' : 0;
		(*sv == '-') ? (*pf)->cf[1] = '-' : 0;
		(*sv == '+') ? (*pf)->cf[2] = '+' : 0;
		(*sv == ' ') ? (*pf)->cf[3] = ' ' : 0;
		if (*sv == '0' && f)
		{
			(*pf)->cf[4] = '0';
			f = 1;
		}
		(!ft_isdigit(*sv)) ? f = 1 : 0;
	}
	if (ft_isprintf_up_spec(*(--sv)))
	{
		(*pf)->cl = ft_tolower(*sv);
		(*pf)->sm = 3;
	}
	else
		(*pf)->cl = *sv;
}

static void		ft_size_spec(char *sv, t_printf **pf)
{
	t_sequence	spec;

	spec = beer;
	while (*(++sv))
	{
		if (*sv == 'h')
		{
			if (*(sv + 1) == 'h')
				spec = hh;
			else
				spec = ((*(sv - 1) == 'h') && *(sv + 1) != 'h') ? spec : h;
		}
		(*sv == 'l' && l > spec) ? spec = l : 0;
		(*sv == 'j' && j > spec) ? spec = j : 0;
		(*sv == 'z' && z > spec) ? spec = z : 0;
		(*sv == 'l' && *(sv + 1) == 'l' && ll > spec) ? spec = ll : 0;
	}
	((*pf)->sm < (char)spec) ? (*pf)->sm = (char)spec : 0;
	((*pf)->cl == 'p') ? (*pf)->sm = z : 0;
	((*pf)->cl == 'p') ? (*pf)->cf[0] = '#' : 0;
	((*pf)->cl == 'o') ? (*pf)->base = 8 : 0;
	((*pf)->cl == 'X') ? (*pf)->base = 16 : 0;
	((*pf)->cl == 'x' || (*pf)->cl == 'p') ? (*pf)->base = 16 : 0;
}

static void		ft_minfld_presc(char *sv, t_printf **pf, va_list *pc, char f)
{
	while (*(++sv))
	{
		if (((*sv >= '1' && *sv <= '9') || f == 3 || f == 4) && f)
		{
			f == 1 ? (*pf)->min_field = (int)ft_atosize_t(sv) : 0;
			f == 2 ? (*pf)->presc = (int)ft_atosize_t(sv) : 0;
			f = 0;
		}
		else if (*sv == '.' && *(sv + 1) == '*')
			(*pf)->presc = va_arg(*pc, int);
		else if (*sv == '.')
		{
			f = 2;
			(*pf)->presc = 0;
		}
		else if (*sv == '*' && *(sv - 1) != '.')
			(*pf)->min_field = va_arg(*pc, int);
		else if (!(*sv >= '1' && *sv <= '9'))
			f = 1;
	}
	(*pf)->presc < -1 ? (*pf)->presc = -1 : 0;
	(*pf)->min_field < 0 ? (*pf)->cf[1] = '-' : 0;
	(*pf)->min_field < 0 ? (*pf)->min_field = -(*pf)->min_field : 0;
}

void			ft_s_spec(t_printf **pf, char *sv, va_list *pc)
{
	ft_s_printf_clr(pf);
	(*pf)->lspc = 0;
	while (*(++sv))
	{
		++(*pf)->lspc;
		if (ft_isascii(*sv) && !ft_isprintf_spec(*sv))
			break ;
	}
	(*pf)->spec = ft_strnfjoin((*pf)->spec, sv - (*pf)->lspc, (*pf)->lspc + 1);
	ft_flags((*pf)->spec, pf);
	ft_size_spec((*pf)->spec, pf);
	ft_minfld_presc((*pf)->spec, pf, pc, 1);
}

int				ft_printf(char *sv, ...)
{
	va_list		pc;
	t_printf	*pf;

	if ((pf = ft_s_printf_new()) == NULL)
		return (-1);
	va_start(pc, sv);
	if (ft_strlen(sv) == 1 && *sv == '%')
		return (0);
	ft_making_move(&pf, &pc, sv);
	va_end(pc);
	ft_puppies_killa(&pf);
	return (pf->lnpr);
}

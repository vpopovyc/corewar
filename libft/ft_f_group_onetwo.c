/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_group_onetwo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:52:40 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/06 14:42:31 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fprintf.h"

static	void		ft_fshit(t_fprintf **pf)
{
	char	prev_c;
	char	base;
	char	tc;

	tc = *((*pf)->tx);
	base = (*pf)->base;
	prev_c = *((*pf)->spec + (*pf)->lspc - 1);
	if ((prev_c == '.' || prev_c == '0') && (*pf)->presc <= 0)
	{
		*((*pf)->tx) == '0' ? (*pf)->ltx = 0 : 0;
		tc == '0' ? (*pf)->cf[4] = '*' : 0;
		base == 8 && (*pf)->cf[0] == '#' && tc == '0' ? ++(*pf)->lnpr : 0;
		base == 8 && (*pf)->cf[0] == '#' ? (*pf)->sign = '0' : 0;
	}
	if ((*pf)->min_field < 0)
		(*pf)->cf[4] == '0' && tc == '0' ? (*pf)->presc = (*pf)->min_field : 0;
}

static	void		ft_fgroup1_sign(t_fprintf **pf)
{
	(*pf)->ltx = (int)ft_strlen((*pf)->tx);
	((*pf)->cf[3] == ' ' && (*pf)->tx[0] != '-') ? (*pf)->sign = ' ' : 0;
	((*pf)->cf[2] == '+' && (*pf)->tx[0] != '-') ? (*pf)->sign = '+' : 0;
	((*pf)->tx[0] == '-') ? (*pf)->sign = '-' : 0;
	((*pf)->tx[0] == '-') ? (*pf)->presc += 1 : 0;
	((*pf)->tx[0] == '-') ? (*pf)->tx += 1 : 0;
	((*pf)->sign == ' ' || (*pf)->sign == '+') ? --(*pf)->min_field : 0;
	((*pf)->sign == ' ' || (*pf)->sign == '+') ? ++(*pf)->lnpr : 0;
	ft_fshit(pf);
}

static	void		ft_fgroup2_sign(t_fprintf **pf)
{
	(*pf)->ltx = (int)ft_strlen((*pf)->tx);
	if (((*pf)->cf[0] == '#' && (*pf)->base != 10))
	{
		((*pf)->base == 8 && *((*pf)->tx) != '0') ? --(*pf)->presc : 0;
		((*pf)->base == 8 && *((*pf)->tx) != '0') ? --(*pf)->min_field : 0;
		((*pf)->base == 8 && *((*pf)->tx) != '0') ? ++(*pf)->lnpr : 0;
		((*pf)->base == 8 && *((*pf)->tx) != '0') ? (*pf)->sign = '0' : 0;
		if ((*pf)->base == 16 && (*((*pf)->tx) != '0' || (*pf)->cl == 'p'))
		{
			(*pf)->min_field -= 2;
			(*pf)->lnpr += 2;
			(*pf)->hex = ((*pf)->cl == 'x' || (*pf)->cl == 'p') ? 'x' : 'X';
			(*pf)->sign = '0';
		}
	}
	((*pf)->cl == 'x' || (*pf)->cl == 'p') ? ft_loweralize((*pf)->tx) : 0;
	ft_fshit(pf);
}

void				ft_fgroup1(t_fprintf **pf, va_list *pc)
{
	if ((*pf)->sm == 0)
		(*pf)->tx = ft_sstoab(va_arg(*pc, int), 10);
	else if ((*pf)->sm == 1)
		(*pf)->tx = ft_sstoab((signed char)va_arg(*pc, int), 10);
	else if ((*pf)->sm == 2)
		(*pf)->tx = ft_sstoab((short)va_arg(*pc, int), 10);
	else if ((*pf)->sm == 3)
		(*pf)->tx = ft_sstoab(va_arg(*pc, long), 10);
	else if ((*pf)->sm == 4)
		(*pf)->tx = ft_sstoab(va_arg(*pc, long long), 10);
	else if ((*pf)->sm == 5)
		(*pf)->tx = ft_sstoab(va_arg(*pc, intmax_t), 10);
	else if ((*pf)->sm == 6)
		(*pf)->tx = ft_sstoab(va_arg(*pc, ssize_t), 10);
	ft_fgroup1_sign(pf);
	ft_fgroup_field(pf);
	if ((*pf)->lnpr == -1)
		return ;
	ft_fgroup_one_output(pf);
}

void				ft_fgroup2(t_fprintf **pf, va_list *pc)
{
	char	bs;

	bs = (*pf)->base;
	if ((*pf)->sm == 0)
		(*pf)->tx = ft_stoab(va_arg(*pc, unsigned int), bs);
	else if ((*pf)->sm == 1)
		(*pf)->tx = ft_stoab((unsigned char)va_arg(*pc, unsigned int), bs);
	else if ((*pf)->sm == 2)
		(*pf)->tx = ft_stoab((unsigned short)va_arg(*pc, unsigned int), bs);
	else if ((*pf)->sm == 3)
		(*pf)->tx = ft_stoab(va_arg(*pc, unsigned long), bs);
	else if ((*pf)->sm == 4)
		(*pf)->tx = ft_stoab(va_arg(*pc, unsigned long long), bs);
	else if ((*pf)->sm == 5)
		(*pf)->tx = ft_stoab(va_arg(*pc, uintmax_t), bs);
	else if ((*pf)->sm == 6)
		(*pf)->tx = ft_stoab(va_arg(*pc, size_t), bs);
	ft_fgroup2_sign(pf);
	ft_fgroup_field(pf);
	if ((*pf)->lnpr == -1)
		return ;
	ft_fgroup_two_output(pf);
}

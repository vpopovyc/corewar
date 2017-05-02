/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:21:16 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/06 15:04:37 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_PRINTF_H
# define __FT_PRINTF_H
# include "libft.h"

typedef	struct	s_printf
{
	char		*ft;
	char		*spec;
	int			nf;
	int			lspc;
	int			mnpr;
	int			lnpr;
	int			min_field;
	int			presc;
	char		sm;
	char		cl;
	char		*cf;
	char		*tx;
	int			ltx;
	char		prefix;
	int			prx;
	char		field;
	int			fld;
	char		sign;
	char		hex;
	char		base;
	int			c;
	char		**ws;
	wchar_t		*wc;
}				t_printf;
typedef	enum	e_size_spec
{
	beer,
	hh,
	h,
	l,
	ll,
	j,
	z
}				t_sequence;
void			ft_s_spec(t_printf **pf, char *sv, va_list *pc);
int				ft_printf(char *sv, ...);
void			ft_s_printf_clr(t_printf **pf);
t_printf		*ft_s_printf_new(void);
void			ft_norm(t_printf **new);
void			ft_making_move(t_printf **pf, va_list *pc, char *sv);
ssize_t			ft_check(t_printf **pf);
void			ft_group1(t_printf **pf, va_list *pc);
void			ft_group2(t_printf **pf, va_list *pc);
void			ft_group3(t_printf **pf, va_list *pc);
void			ft_group_one_output(t_printf **pf);
void			ft_group_two_output(t_printf **pf);
void			ft_group_prefix(t_printf **pf);
void			ft_group_field(t_printf **pf);
void			ft_puppies_killa(t_printf **pf);
void			ft_weof_camp(t_printf **pf, va_list *pc);
void			ft_bit_party(t_printf **pf, wchar_t *s);
void			ft_group_other_sign(t_printf **pf);
void			ft_string_sign(t_printf **pf);
#endif

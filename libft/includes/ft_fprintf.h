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

#ifndef __FT_FPRINTF_H
# define __FT_FPRINTF_H
# include "libft.h"

typedef	struct	s_fprintf
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
	int			fd;
}				t_fprintf;

void			ft_fs_spec(t_fprintf **pf, char *sv, va_list *pc);
int				ft_fprintf(char *sv, int fd, ...);
void			ft_s_fprintf_clr(t_fprintf **pf);
t_fprintf		*ft_s_fprintf_new(void);
void			ft_fnorm(t_fprintf **new);
void			ft_fmaking_move(t_fprintf **pf, va_list *pc, char *sv);
ssize_t			ft_fcheck(t_fprintf **pf);
void			ft_fgroup1(t_fprintf **pf, va_list *pc);
void			ft_fgroup2(t_fprintf **pf, va_list *pc);
void			ft_fgroup3(t_fprintf **pf, va_list *pc);
void			ft_fgroup_one_output(t_fprintf **pf);
void			ft_fgroup_two_output(t_fprintf **pf);
void			ft_fgroup_prefix(t_fprintf **pf);
void			ft_fgroup_field(t_fprintf **pf);
void			ft_fpuppies_killa(t_fprintf **pf);
void			ft_fweof_camp(t_fprintf **pf, va_list *pc);
void			ft_fbit_party(t_fprintf **pf, wchar_t *s);
void			ft_fgroup_other_sign(t_fprintf **pf);
void			ft_fstring_sign(t_fprintf **pf);
#endif

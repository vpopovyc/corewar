/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:16:14 by dkosolap          #+#    #+#             */
/*   Updated: 2017/06/06 19:29:02 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COREWAR_H
# define __COREWAR_H

# include "../op.h"
# include "../libft/includes/libft.h"
# include <stdio.h>
# include "s_corewar.h"

typedef struct s_init_screen	t_init_screen;

typedef struct			s_player
{
	char				*name;
	char				*comment;
	char				*code;
	int					number;
	unsigned int		size;
	struct s_player		*next;
}						t_player;

typedef struct			s_carriage
{
	unsigned int		position;
	void				(*f)(t_corewar *src, struct s_carriage *head);
	int					comand_cycle;
	int					arg[4];
	unsigned int		live_in_cycle;
	int					reg[REG_NUMBER];
	int					carry;
	int					i;
	char				name;
	char				*name_p;
	struct s_carriage	*next;
}						t_carriage;

void					ft_error(int n);
t_player				*ft_valid_cor(int fd, size_t len, size_t n_read);
void					dk_pars_arg(int ac, char **av, t_corewar *cor, int i);
int						find_nbr_ply(t_player *ply, int nbr);
void					dk_sort_ply(t_player **ply, int nbr);
void					add_ply_back(t_player **ply, t_player *tmp);

void					ft_create_field_and_carriage(t_corewar *src, int n,
						int num, char *p);
void					ft_check_cycle_to_die(t_corewar *s, int n_live, int i);
t_carriage				*ft_del_carriage(t_carriage *src, t_carriage *del);
t_carriage				*ft_check_del_carriege(t_corewar *d, t_carriage *src);

void					ft_check_mem_cell(t_carriage *head, char *field);
void					ft_algoritm(t_corewar *src);
void					ft_increment_cycle(t_corewar *src, t_carriage *head);
void					dk_dump(char *addr);
void					sub_meta_bold(char *src);
int						count_car(t_carriage *head);
void					ft_algoritm_visual(t_corewar *src, t_init_screen *i);

void					ft_live(t_corewar *data, t_carriage *src);
void					ft_ld(t_corewar *data, t_carriage *src);
void					ft_st(t_corewar *data, t_carriage *src);
void					ft_add(t_corewar *data, t_carriage *src);
void					ft_sub(t_corewar *data, t_carriage *src);
void					ft_and_or_xor(t_corewar *d, t_carriage *s);
void					ft_and_or_xor_5(t_corewar *d, t_carriage *s,
						char op, char c);
void					ft_zjmp(t_corewar *data, t_carriage *src);
void					ft_ldi_lldi(t_corewar *data, t_carriage *src);
void					ft_fork(t_corewar *data, t_carriage *src);
void					ft_lld(t_corewar *data, t_carriage *src);
void					ft_lfork(t_corewar *data, t_carriage *src);
void					ft_aff(t_corewar *data, t_carriage *src);
void					ft_sti(t_corewar *data, t_carriage *src);

int						ft_inc_index(t_carriage *src);
int						ft_fix(int index);
void					ft_take_arg(t_corewar *data, t_carriage *src,
						int i, int comand);
t_carriage				*ft_create_carriage(unsigned int posinion, int num,
						t_carriage *data, char *name);

void					ft_write_meta(t_corewar *src, char name, int p);
void					dk_field_meta(char *meta, int name, int s, int len);
void					ft_write_meta(t_corewar *src, char name, int p);
void					(*g_funcs[16])(struct s_corewar *src,
						struct s_carriage *head);
int						ft_take_ind(t_corewar *data, int index);
#endif

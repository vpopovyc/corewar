/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 10:53:53 by dkosolap          #+#    #+#             */
/*   Updated: 2017/06/02 12:25:15 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COREWAR_H
# define __COREWAR_H

# include "../op.h"
# include "../libft/includes/libft.h"
# include <stdio.h>

typedef struct		s_player
{
	char			*name;
	char			*comment;
	char			*code;
	int				number;
	unsigned int	size;
	struct s_player	*next;
}					t_player;

typedef struct		s_corewar t_corewar;

typedef struct		s_carriage
{
	unsigned int	position;			//  индекс позиции каретки в игровом поле
	void			(*f)(t_corewar *src, struct s_carriage *head);	//ссылка на функцию которую нужно будет выполнить
	int				comand_cycle;		//циклы после которых выполняется команда
	int				arg[4];				//opcode_arg, и три аргумента
	unsigned int	live_in_cycle;		// количество сказаных live в текущем cycle_to_die
	int				reg[REG_NUMBER];	//регистры
	int				carry;
	int 			i;                   // нужно для визуализации, руками и не руками трогать нельзя
    char            name;
	char			*name_p;
	struct s_carriage *next;
}					t_carriage;

typedef struct		s_corewar
{
	t_player		*players; // список игроков и их даные из файла для валидации
	t_carriage		*carriage; // спичок кареток
	char			*field; // игровое поле
	char 			*meta_data;
	char 			*meta_bold;
	int				*players_live; /* масив размером с количество игроков,
	каждый елемент число сказаных live с именем конкретного
	игрока( индекс номер игрока на карте) */

	unsigned int	curent_cycle; // тукущий цикл, общий счетчик циклов
	unsigned int	cycle_to_die; // количество циклов к смерти, будет изменяться на дельту
	unsigned int	last_cycle_to_die; // счетчик циклов к смерти
	unsigned int	n_check; // цикл для MAX_CHECKS
	int				fdump; // елси число не (-1) значит вивести дамп после fdump циклов
	int				verbose; // визуальный режим
	int				count_ply;
	int				sec_cycle;
    char            *winer;
}					t_corewar;




void				ft_error(int n);
t_player 		   *ft_valid_cor(int fd, size_t len, size_t n_read);
void				dk_pars_arg(int argc, char **argv, t_corewar *cor, int i);
int					find_nbr_ply(t_player *ply, int nbr);
void				dk_sort_ply(t_player **ply, int nbr);
void				add_ply_back(t_player **ply, t_player *tmp);


void                ft_create_field_and_carriage(t_corewar *src, int n, int num); // создание игрового поля и кареток
void                ft_check_cycle_to_die(t_corewar *src, int n_live); // проверка для уменьшения cycle_to_die
t_carriage          *ft_del_carriage(t_carriage *src, t_carriage *del); // удаление каретки
t_carriage			*ft_check_del_carriege(t_carriage *src);

void				ft_algoritm(t_corewar *src);
void				dk_dump(char *addr);

int     			ft_inc_index(t_carriage *src);
int     			ft_fix(int index);
void    			ft_take_arg(t_corewar *data, t_carriage *src, int i, int comand); // i == 0  / вызываеться при командах с опкодом
t_carriage			*ft_create_carriage(unsigned int posinion, int num, t_carriage *data, char *name);
void				ft_live(t_corewar *data, t_carriage *src);
void				ft_ld(t_corewar *data, t_carriage *src);
void			    ft_st(t_corewar *data, t_carriage *src);
void				ft_add(t_corewar *data, t_carriage *src);
void				ft_sub(t_corewar *data, t_carriage *src);
void                ft_and_or_xor(t_corewar *d, t_carriage *s);
void				ft_zjmp(t_corewar *data, t_carriage *src);
void				ft_ldi_lldi(t_corewar *data, t_carriage *src);
void    			ft_fork(t_corewar *data, t_carriage *src);
void				ft_lld(t_corewar *data, t_carriage *src);
void				ft_lfork(t_corewar *data, t_carriage *src);
void				ft_aff(t_corewar *data, t_carriage *src);

void                ft_write_meta(t_corewar *src, char name, int position); // запись имени игрока в масив метаданных для визуального отображения
void				dk_field_meta(char *meta, int name, int len);
void                ft_sti(t_corewar *data, t_carriage *src);
void                ft_write_meta(t_corewar *src, char name, int position);
void				(*g_funcs[16])(struct s_corewar *src, struct s_carriage *head);//Указатель на функцию
int					ft_take_ind(t_corewar *data, int index);
#endif

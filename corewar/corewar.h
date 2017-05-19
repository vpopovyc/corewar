/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 10:53:53 by dkosolap          #+#    #+#             */
/*   Updated: 2017/05/08 10:53:54 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COREWAR_H
# define __COREWAR_H

# include "op.h"
# include "libft.h"
# include "stdio.h"

typedef struct		s_player
{
	char			*name;
	char			*comment;
	char			*code;
	int				number;
	unsigned int	size;
	struct s_player	*next;
}					t_player;

typedef struct		s_op
{
	char			*name;
	int				binary_code;
	int				len[3];
	int				op_code;
	int				cycle;
	char			*comment;
	int				octal;
	int				dependence_carry;
}					t_op;

typedef struct		s_carriage
{
	unsigned int	posinion;			//  индекс позиции каретки в игровом поле
	void			(*f)(int args[4]);	//ссылка на функцию которую нужно будет выполнить
	int				comand_cycle;		//циклы после которых выполняется команда
	int				arg[4];				//opcode_arg, и три аргумента
	unsigned int 	last_live;			//количество циклов после последня лайфа
	unsigned int	live_in_cycle;		// количество сказаных live в текущем cycle_to_die
	int				reg[REG_NUMBER];	//регистры
	struct s_carriage *next;
}					t_carriage;

typedef struct		s_corewar
{
	t_player		*players; // список игроков и их даные из файла для валидации
	t_carriage		*carriage; // спичок кареток
	char			*game_field; // игровое поле
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
}					t_corewar;




void				ft_error(int n);
t_player 		   *ft_valid_cor(int fd, size_t len, size_t n_read);
void				dk_pars_arg(int argc, char **argv, t_corewar *cor, int i);
void                ft_create_field_and_carriage(t_corewar *src, int free_space, int n);
void    ft_check_cycle_to_die(t_corewar *src, int n_live); // проверка для уменьшения cycle_to_die

#endif

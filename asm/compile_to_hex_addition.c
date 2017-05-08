/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_to_hex_addition.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:26:32 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/08 22:00:28 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

#define MAX_SHR_SIZE 		4
#define HIGH_FOUR_BITS_SHR	12
#define CODE_BYTE_EXIST 	1
#define SMALL_LABEL			1

#define CHAR 	1
#define SHRT 	2
#define UINT	3

#define FIRSTARG	6
#define C_TAKAYA_C	3

int		g_carrige = 0;
int		g_new_line = 0;
int		g_current_command = 0;
// int		g_space = 0;

void 	man_var(char flag, int fd)
{
	while (flag)
	{
		++g_new_line;
		++g_carrige;
		if (g_new_line == NEW_LINE_NEEDED)
			write(fd, "\n", 1);
		else if (!(g_carrige % 2))
			write(fd, " ", 1);
		--flag;
	}
}

void 	write_bc_char(char c, int fd)
{
	char c_t;

 	c_t = char_to_hex(erase_low_bits(c));
	write (fd, &(c_t), 1);
	c_t = char_to_hex(erase_high_bits(c));
	write (fd, &(c_t), 1);
	man_var(CHAR, fd);
}

void 	write_bc_shr(short key, int fd)
{
	char 	current_4_bits;
	char 	step_right;
	int 	i;

	i = 0;
	step_right = HIGH_FOUR_BITS_SHR;
	while (i < MAX_SHR_SIZE)
	{
		if (i == 2)
			man_var(SHRT, fd);
		current_4_bits = (char)(key >> step_right);
		current_4_bits = char_to_hex(erase_high_bits(current_4_bits));
		write(fd, &(current_4_bits), 1);
		step_right -= 4;
		++i;
	}
}

void 	write_bc_int(int key, int fd)
{
	char 	current_4_bits;
	char 	step_right;
	int 	i;

	i = 0;
	step_right = HIGH_FOUR_BITS;
	while (i < MAX_UINT_SIZE - 1)
	{
		if (i == TWO_BYTES_SPR)
			man_var(UINT, fd);
		current_4_bits = (char)(key >> step_right);
		current_4_bits = char_to_hex(erase_high_bits(current_4_bits));
		write(fd, &(current_4_bits), 1);
		step_right -= 4;
		++i;
	}
	man_var(CHAR, fd);
}

void 	insert_op_code(char op_code, char *name, int fd)
{
	if (ft_strcmp("", name)) /* name not "empty" */
		write_bc_char(op_code, fd);
	else
		return ;
}

void	insert_code_byte(char code_byte, char reference, int fd)
{
	if (reference == CODE_BYTE_EXIST)
		write_bc_char(code_byte, fd);
	else
		return ;
}

void 	insert_registres(char *reg, int fd)
{
	char *t_reg;

	t_reg = reg + 1;
	write_bc_char((char)ft_atoi(t_reg), fd);
}

void 	insert_indirect(char *ind, t_hash *table, int fd)
{
	t_hash 		*elem;
	short		encode;

	elem = NULL;
	if (*ind == LABEL_CHAR)
	{
		elem = get_item(ind + 1, table);
		encode = elem->bytes - g_current_command;
	}
	else
		encode = (short)ft_atoi(ind);

	write_bc_shr(encode, fd);
	// man_var(SHRT, fd);
}

void 	insert_direct(char *dir, char label_size, t_hash *table, int fd)
{
	t_hash 	*elem;
	int		encode_big;
	short	encode_small;

	elem = NULL;
	if (*(dir + 1) == LABEL_CHAR)
	{
		if (label_size == SMALL_LABEL)
		{
			elem = get_item(dir + 2, table);
			encode_small = (short)elem->bytes - g_current_command;
			write_bc_shr(encode_small, fd);
			// man_var(SHRT, fd);
		}
		else
		{
			elem = get_item(dir + 2, table);
			encode_big = (int)ft_atoi(dir + 2);
			encode_big = (int)elem->bytes - g_current_command;
			write_bc_int(encode_big, fd);
			// man_var(UINT, fd);
		}
	}
	else
	{
		if (label_size == SMALL_LABEL)
		{
			encode_small = (short)ft_atoi(dir + 1);
			write_bc_shr(encode_small, fd);
			// man_var(SHRT, fd);
		}
		else
		{
			encode_big = (int)ft_atoi(dir + 1);
			write_bc_int(encode_big, fd);
			// man_var(UINT, fd);
		}
	}
}

void	insert_args(char hex_code, char *arg, t_hash *table, int fd, int i)
{
	if (hex_code == 1)
		insert_registres(arg, fd);
	else if (hex_code == 2)
		insert_direct(arg, g_op[i].label_size, table, fd);
	else if (hex_code == 3)
		insert_indirect(arg, table, fd);
	else
		return ;
}

static void	write_command_bc(t_comand *comand, t_hash *table, int fd)
{
	int		i;

	i = 0;
	while (g_op[i].name)
	{
		if (ft_strequ(g_op[i].name, comand->name))
			break ;
		i++;
	}
	g_current_command = g_carrige;
	insert_op_code(g_op[i].op_code, comand->name, fd);
	insert_code_byte(comand->hex_code, g_op[i].code_byte, fd);
	insert_args((comand->hex_code >> FIRSTARG) & C_TAKAYA_C, comand->arg1, table, fd, i);
	insert_args((comand->hex_code & SECONDARG) >> 4, comand->arg2, table, fd, i);
	insert_args((comand->hex_code & THIRDARG) >> 2, comand->arg3, table, fd, i);
}

static void	commands_to_bc(t_hash *table, t_label *head, int fd)
{
	t_label		*label;
	t_comand	*comand;

	label = head;
	while (label)
	{
		comand = label->comand;
		while (comand)
		{
			write_command_bc(comand, table, fd);
			comand = comand->next;
		}
		label = label->next;
	}
}

void step_to_byte_code(t_hash *table, t_label *head, t_bc_header *h_bc, int fd)
{
	print_header_bc(h_bc, fd);
	commands_to_bc(table, head, fd);
	close(fd);
}

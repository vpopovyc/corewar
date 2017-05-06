/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bc_to_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:02:08 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/04 14:02:40 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"
/*
** Writes space into resulting array, refreshing space counter
*/
void		place_space(char *prog_name, int *space)
{
	*prog_name = ' ';
	*space = NO_SPACE;
}
/*
** Writes new_line into resulting array, refreshing space and nl counters
*/
void		place_new_line(char *prog_name, int *space, int *new_line)
{
	*prog_name = '\n';
	*space = NO_SPACE; 
	*new_line = BEGIN_OF_LINE;
}
/*
** Counts number of bytes in accordance to data structure alignment
** And returns aligned size
*/
int			count_number_of_bytes(int key_length)
{
	if ((key_length + 1) % 4)
		return (find_num_of_bytes(key_length + 1));
	else
		return (key_length + 1);
}
/*
** Writes byte-code of char reference to prog array 
** It splits one char of reference into two diff chars 
** First char contain four high bits of char reference, as second contain four lower
*/
void		write_bc_to_header(char **prog, char **reference, int i)
{
	**prog = char_to_hex(erase_low_bits(**reference));
    ++(*prog);
	**prog = char_to_hex(erase_high_bits(**reference));
	++(*prog);
	if (i < COMMENT_LENGTH)
		++(*reference);
}
/*
** Temp variables changes, that needed in header_comment_bc() and header_name_bc()
*/
void		variables_moves(int *space, int *new_line, int *i)
{
	*space <<= 1;
	++(*new_line);
	++(*i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:19:26 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/03 15:19:45 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

static void		header_uint_bc(char *magic, int key)
{
	char 	current_4_bits;
	char 	step_right;
	int 	i;

	i = 0;
	step_right = HIGH_FOUR_BITS;
	while (i < MAX_UINT_SIZE)
	{
		if (i == TWO_BYTES_SPR)
			magic[i] = ' ';
		else
		{
			current_4_bits = (char)(key >> step_right);
			current_4_bits = erase_high_bits(current_4_bits);
			magic[i] = char_to_hex(current_4_bits);
			step_right -= 4;
		}
		++i;
	}
	magic[MAX_UINT_SIZE] = '\0';
}

static void		header_name_bc(char *prog_name, char *reference)
{
	int 	num_of_bytes;
	int 	i;
	int 	space;
	int 	new_line;

	i = 0;
	space = NO_SPACE;
	new_line = BEGIN_OF_LINE_AFTER_MAGIC;
	num_of_bytes = count_number_of_bytes(PROG_NAME_LENGTH);
	while (i < num_of_bytes)
	{
		if (new_line == NEW_LINE_NEEDED)
			place_new_line(prog_name++, &space, &new_line);
		else if (space == SPACE_NEEDED)
			place_space(prog_name++, &space);
		else
		{
			write_bc_to_header(&prog_name, &reference, i);
			variables_moves(&space, &new_line, &i);
		}
	}
	*prog_name = '\0';
}

static void		header_comment_bc(char *comment, char *reference)
{
	int 	num_of_bytes;
	int 	i;
	int 	space;
	int 	new_line;

	i = 0;
	space = NO_SPACE;
	new_line = BEGIN_OF_LINE_AFTER_PS;
	num_of_bytes = count_number_of_bytes(COMMENT_LENGTH);
	while (i < num_of_bytes)
	{
		if (new_line == NEW_LINE_NEEDED)
			place_new_line(comment++, &space, &new_line);
		else if (space == SPACE_NEEDED)
			place_space(comment++, &space);
		else
		{
			write_bc_to_header(&comment, &reference, i);
			variables_moves(&space, &new_line, &i);
		}
	}
	*comment = '\0';
}

void	header_bc_init(t_bc_header *sv, header_t *header)
{
	header_uint_bc(sv->magic, header->magic);
	printf("%s ", sv->magic);
	header_name_bc(sv->prog_name, header->prog_name);
	printf("%s ", sv->prog_name);
	header_uint_bc(sv->prog_size, header->prog_size);
	printf("%s ", sv->prog_size);
	header_comment_bc(sv->comment, header->comment);
	printf("%s\n", sv->comment);
}

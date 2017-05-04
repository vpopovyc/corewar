/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:57:51 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/02 17:57:53 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

void	fill_header(header_t *sv)
{
	sv->magic = COREWAR_EXEC_MAGIC;

	for (int i = 0; i < PROG_NAME_LENGTH; i++)
		sv->prog_name[i] = 'A';
	sv->prog_name[PROG_NAME_LENGTH] = '\0';

	for (int j = 0; j < COMMENT_LENGTH; j++)
		sv->comment[j] = 'B';
	sv->comment[COMMENT_LENGTH] = '\0';

	sv->prog_size = PROG_SIZE;
}

int		main(void)
{
	header_t 		header;
	t_bc_header		sv;

	fill_header(&header);
	header_bc_init(&sv, &header);
	// printf("name: %s\ncomment: %s\nprog_size: %i\nmagic: %x\n", header.prog_name, 
	// header.comment, header.prog_size, header.magic);
	
	return (0);
}

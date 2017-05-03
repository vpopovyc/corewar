/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_code_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:49:01 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/02 17:49:07 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BYTE_CODE_HEADER_H
# define __BYTE_CODE_HEADER_H

# include "../libft/includes/libft.h"
# include "../op.h"

/*
** header magic
*/
# define TWO_BYTES_SPR 				4
# define MAX_UINT_SIZE 				9
# define BASE						16
# define HIGH_FOUR_BITS				28
# define HEX_CHARS					"0123456789abcdef"
/*
** header name
*/
# define BEGIN_OF_LINE				0
# define NO_SPACE					1
# define BEGIN_OF_LINE_AFTER_MAGIC	4
# define SPACE_NEEDED 				4
# define NEW_LINE_NEEDED			16
# define BC_PROG_LENGTH 			PROG_NAME_LENGTH + (PROG_NAME_LENGTH / 2)
/*
** header program size
*/
# define PROG_SIZE 					0x820202ff
/*
** header comment
*/
# define BC_COMMENT_LENGTH			COMMENT_LENGTH + (COMMENT_LENGTH / 2)
# define BEGIN_OF_LINE_AFTER_PS		12


typedef struct		s_bc_header
{
  char				magic[MAX_UINT_SIZE + 1];
  char				prog_name[BC_PROG_LENGTH + 1];
  char				prog_size[MAX_UINT_SIZE + 1];
  char				comment[BC_COMMENT_LENGTH + 1];
}					t_bc_header;

void	header_bc_init(t_bc_header *sv, header_t *header);
char 	char_to_hex(char pv);
char 	erase_high_bits(char pv);
char 	erase_lower_bits(char pv);
#endif
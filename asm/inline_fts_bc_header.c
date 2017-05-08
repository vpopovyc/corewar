/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_fts_bc_header.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:19:44 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/08 14:27:42 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"
/*
** Converts char to hex bytecode
*/
char 	char_to_hex(char pv)
{
	return ((char)HEX_CHARS[pv % BASE]);
}
/*
** Sets high bits of byte in 0
*/
char 	erase_high_bits(char pv)
{
	return (pv ^ ((pv >> 4) << 4));
}
/*
** Sets low bits of byte in 0
*/
char 	erase_low_bits(char pv)
{
	return (pv >> 4 ^ ((pv >> 8) << 4));
}
/*
** Formula that needed for count_number_of_bytes()
*/
int 	find_num_of_bytes(int length)
{
	return ((4 - (length % 4)) + length);
}

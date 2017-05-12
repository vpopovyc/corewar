/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_to_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 11:58:00 by mkrutik           #+#    #+#             */
/*   Updated: 2017/05/12 12:00:07 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

char	ft_arg_to_binary(char b1, char b2, char b3)
{
	char byte;

	byte = 0;
	byte |= b3 << 2;
	byte |= b2 << 4;
	byte |= b1 << 6;
	return (byte);
}

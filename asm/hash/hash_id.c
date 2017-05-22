/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_id.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:54:50 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/22 18:54:54 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/hash.h"

t_uint	str_hash(char *sv)
{
	t_uint	hash;

	hash = HASH_FNV;
	while (*sv)
	{
		hash = (MAGIC_NUMBER_FNV * hash) ^ *sv;
		++sv;
	}
	return (hash);
}

t_uint	hash_id(t_uint hash)
{
	return (hash % SIZEOFTABLE);
}

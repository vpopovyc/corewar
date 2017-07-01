/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:46:44 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/06/05 20:46:07 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/hash.h"

int		key_exist(char *newkey, t_hash *table)
{
	t_hash	*ptr;
	int		id;

	id = hash_id(str_hash(newkey));
	ptr = table[id].collision;
	if (ft_strequ(table[id].key, newkey))
		return (1);
	else
	{
		while (ptr)
		{
			if (ft_strequ(ptr->key, newkey))
				return (1);
			ptr = ptr->collision;
		}
	}
	return (0);
}

t_hash	*append_key_hash(char *newkey, t_hash *collision, int bytes)
{
	t_hash	*ptr;
	t_hash	*new;

	new = (t_hash*)ft_memalloc(sizeof(t_hash));
	new->key = newkey;
	new->bytes = bytes;
	ptr = collision;
	if (ptr == FIRST_COLLISION)
		collision = new;
	else
	{
		while (ptr->collision)
			ptr = ptr->collision;
		ptr->collision = new;
	}
	return (collision);
}

void	add_key_hash(char *newkey, int bytes, t_hash *table)
{
	int		id;

	id = hash_id(str_hash(newkey));
	if (!table[id].key)
	{
		table[id].key = ft_strdup(newkey);
		table[id].bytes = bytes;
	}
	else if (!key_exist(newkey, table))
		table[id].collision = append_key_hash(ft_strdup(newkey),
				table[id].collision, bytes);
}

t_hash	*get_item(char *key, t_hash *table)
{
	int		id;
	t_hash	*ptr;

	id = hash_id(str_hash(key));
	ptr = table[id].collision;
	if (ft_strequ(table[id].key, key))
		return (&table[id]);
	else
	{
		while (ptr)
		{
			if (ft_strequ(ptr->key, key))
				return (ptr);
			ptr = ptr->collision;
		}
	}
	return ((t_hash*)NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 16:00:29 by rvolovik          #+#    #+#             */
/*   Updated: 2017/06/05 20:17:20 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HASH_H
# define __HASH_H

# include "../../libft/includes/libft.h"

# define MAGIC_NUMBER_FNV			16777619
# define HASH_FNV					2166136261
# define SIZEOFTABLE				64
# define FIRST_COLLISION			NULL

typedef unsigned					t_uint;

typedef struct						s_command
{
	char							*args[3];
	struct s_command				*next;
	int								bytes;
	char							codebyte;
	char							opcode;
}									t_command;

typedef struct						s_hash
{
	char							*key;
	int								bytes;
	t_command						*commands;
	struct s_hash					*collision;
}									t_hash;

/*
**	hash.c
*/

int									key_exist(char *newkey, t_hash *table);
/*t_hash								*append_key_hash(char *newkey,
	t_hash *table, int id, int bytes);*/
t_hash	*append_key_hash(char *newkey, t_hash *collision, int bytes);
void								add_key_hash(char *newkey, int bytes,
	t_hash *table);
t_hash								*get_item(char *key, t_hash *table);

/*
** hash_id.c
*/

t_uint								str_hash(char *sv);
t_uint								hash_id(t_uint hash);
#endif

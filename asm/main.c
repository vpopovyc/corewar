/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 16:45:27 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/08 18:29:11 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

void		ft_open(char *name, t_gamer *src)
{
	char s[2];

	if ((src->fd = open(name, O_RDONLY)) < 0)
		ft_error(3);
	if (read(src->fd, s, 0) < 0)
		ft_error(4);
	if (close(src->fd) < 0)
		ft_error(5);
	src->fd = open(name, O_RDONLY);
}

t_gamer		*init_validation(int argc, char **argv)
{
	t_gamer *new;

	(!(new = (t_gamer*)malloc(sizeof(t_gamer)))) ? ft_error(1) : 0;
	(!(new->src = (header_t*)malloc(sizeof(header_t)))) ? ft_error(1) : 0;
	new->header_bc = (t_bc_header*)ft_memalloc(sizeof(t_bc_header));
	new->table = (t_hash*)ft_memalloc(sizeof(t_hash) * SIZEOFTABLE);
	/* temp */
	new->label = NULL;
	/* temp */
	(argc != 2) ? ft_error(2) : ft_open(argv[1], new);
	new->header = 0;
	new->name = NULL;
	new->comment = NULL;
	ft_validation(new);
	return (new);
}

void print_header_bc(t_bc_header *sv, int fd)
{
	write(fd, sv->magic, ft_strlen(sv->magic));
	write(fd, " ", 1);
	write(fd, sv->prog_name, BC_PROG_LENGTH);
	write(fd, " ", 1);
	write(fd, sv->prog_size, ft_strlen(sv->prog_size));
	write(fd, " ", 1);
	write(fd, sv->comment, ft_strlen(sv->comment));
	write(fd, "\n", 1);
}

int		main(int ac, char **av)
{
	t_gamer		*root;

	root = init_validation(ac, av);
    header_bc_init(root->header_bc, root->src);
	/* temp */
	fill_label_list(&(root->label));
	/* temp */
	fill_hash_table(root->table, root->label, root->header_bc, root->name);
	/* asm */
	// printlabel(root->label);
	// t_hash		*elem;
	// elem = get_item("l2", root->table);
	// printf("key %s byte len %d\n", elem->key, elem->bytes);
	// elem = get_item("live", root->table);
	// printf("key %s byte len %d\n", elem->key, elem->bytes);
	// elem = get_item("empty", root->table);
	// printf("key %s byte len %d\n", elem->key, elem->bytes);
	/* asm */
	/* bc */
	/* bc */
	// ft_write_comands(root, 0, NULL);
	return (0);
}

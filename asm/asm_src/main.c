/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 20:32:50 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/22 20:32:51 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/byte_code_header.h"
#include "../headers/sounds.h"

void	ft_error(int n)
{
	ft_putstr("\033[0;31m");
	(n == 1) ? ft_putstr("Memory allocation error!\n") : 0;
	(n == 2) ? ft_putstr("Wrong number of arguments!\n") : 0;
	(n == 3) ? ft_putstr("File doesn`t open or wrong file name!\n") : 0;
	(n == 4) ? ft_putstr("It`s not possible to read the file!\n") : 0;
	(n == 5) ? ft_putstr("It`s not possible to close the file!\n") : 0;
	(n == 6) ? ft_putstr("Invalid header!\n") : 0;
	(n == 7) ? ft_putstr("Name is too long!\n") : 0;
	(n == 8) ? ft_putstr("Comment is too long!\n") : 0;
	(n == 9) ? ft_putstr("Lexical error: bad label!\n") : 0;
	(n == 10) ? ft_putstr("Lexical error: bad command!\n") : 0;
	(n == 11) ? ft_putstr("Invalid argument: label is not valid.\n") : 0;
	(n == 12) ? ft_putstr("Invalid argument: digit is not valid.\n") : 0;
	(n == 13) ? ft_putstr("Could not get specified arguments\n") : 0;
	(n == 14) ? ft_putstr("Could not find target lable :(\n") : 0;
	(n == 15) ? ft_putstr("New line ?\n") : 0;
	ft_putstr("\033[0m");
	sound(NOK);
	exit(-1);
}

void	check_new_line(int fd)
{
	char	ptr;
	int		offset;

	offset = 0;
	ptr = 0;
	while (--offset)
	{
		lseek(fd, offset, SEEK_END);
		read(fd, &ptr, 1);
		if (ft_isascii((int)ptr) && ptr != ' ' && ptr != '\n' && ptr != '\0')
			ft_error(15);
		else if (ptr == ' ' || ptr == '\0')
			continue ;
		else
			return ;
	}
}

int		main(int ac, char **av)
{
	t_base		*root;

	root = init_validation(ac, av);
	enqueue_labels(&(root->q_label),
		root->table, &(root->reference->prog_size));
	compilation(root->table, &root->q_label, root->reference, root->path);
	ft_putstr("Writing output to ");
	ft_putstr(root->path);
	ft_putstr(".cor\n");
	sound(OK);
	return (0);
}

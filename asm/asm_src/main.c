/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 20:32:50 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/06/05 14:38:27 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/byte_code_header.h"
#include "../headers/sounds.h"

int		g_line = 0;

void	find_delete_comment(char *ln)
{
	char	*ptr;

	ptr = ft_strchr(ln, COMMENT_CHAR);
	if (ptr)
		ft_memset(ptr, ' ', ft_strlen(ptr));
}

void	ft_error(int n, int line)
{
	ft_putstr("\033[0;31m");
	ft_printf("Line [%d] : ", line);
	(n == 1) ? ft_putstr("Memory allocation error!\n") : 0;
	(n == 2) ? ft_putstr("Wrong number of arguments!\n") : 0;
	(n == 3) ? ft_putstr("File doesn`t open or wrong file name!\n") : 0;
	(n == 4) ? ft_putstr("Cannot compile a directory!\n") : 0;
	(n == 5) ? ft_putstr("It`s not possible to close the file!\n") : 0;
	(n == 6) ? ft_putstr("Invalid header!\n") : 0;
	(n == 7) ? ft_putstr("Name is too long!\n") : 0;
	(n == 8) ? ft_putstr("Comment is too long!\n") : 0;
	(n == 9) ? ft_putstr("Lexical error: bad label!\n") : 0;
	(n == 10) ? ft_putstr("Lexical error: bad command!\n") : 0;
	(n == 11) ? ft_putstr("Invalid argument: label is not valid.\n") : 0;
	(n == 12) ? ft_putstr("Invalid argument: ti invalid.\n") : 0;
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
			ft_error(15, g_line);
		else if (ptr == ' ' || ptr == '\0')
			continue ;
		else
			return ;
	}
}

void	vape(t_base *root)
{
	enqueue_labels(&(root->q_label),
		root->table, &(root->reference->prog_size));
	compilation(root->table, &root->q_label, root->reference, root->path);
	ft_putstr("Writing output to ");
	ft_putstr(root->path);
	ft_putstr(".cor\n");
	sound(OK);
}

int		main(int ac, char **av)
{
	t_base	*array[ac - 1];
	int		i;

	i = 0;
	++av;
	close(2);
	if (ac == 1)
		ft_error(2, 0);
	while (i < ac - 1)
	{
		array[i] = init_validation(av[i]);
		vape(array[i]);
		++i;
	}
	return (0);
}

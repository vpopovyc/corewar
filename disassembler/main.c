/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 17:45:43 by rvolovik          #+#    #+#             */
/*   Updated: 2017/06/01 15:16:27 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"
#include <stdio.h>

void	ft_error(int n)
{
	ft_putstr("\x1b[41m");
	(n == 1) ? ft_putstr("Wrong number of arguments!") : 0;
	(n == 2) ? ft_putstr("Doesn`t right file format!") : 0;
	(n == 3) ? ft_putstr("File doesn`t open, maybe wrong file name!") : 0;
	(n == 4) ? ft_putstr("Can`t read from the file!") : 0;
	(n == 5) ? ft_putstr("The file is too large, must be less then 1 mb!") : 0;
	(n == 6) ? ft_putstr("Memory allocation error!") : 0;
	(n == 7) ? ft_putstr("Can`t close file!") : 0;
	(n == 8) ? ft_putstr("Invalid player's binary code!") : 0;
	(n == 9) ? ft_putstr("Wrong comand founded!") : 0;
	(n == 10) ?
			ft_putstr("Length of commands code doesn't match to specified") : 0;
	ft_putstr("\x1b[0m\n\x1b[36m");
	ft_putstr("Usage: ./disasm file.cor");
	ft_putstr("\x1b[0m");
	exit(-1);
}

void	ft_check_file_format(t_desasm *data, char *name)
{
	size_t	len;
	char	*point;

	len = ft_strlen(name);
	point = name + (len - 4);
	if (ft_strcmp(point, ".cor"))
		ft_error(2);
	data->file_name = ft_strsub(name, 0, len - 4);
}

void	ft_open_read_close(t_desasm *data, char *name)
{
	char	tmp[1000000];
	int		fd;
	ssize_t	len;

	if ((fd = open(name, O_RDONLY)) < 0)
		ft_error(3);
	len = read(fd, tmp, 1000000);
	if (len < 0)
		ft_error(4);
	if (len == 1000000 && (read(fd, tmp, 1) != 0))
		ft_error(5);
	data->file_data = ft_strnew(len - 1);
	if (!data->file_data)
		ft_error(6);
	ft_memcpy(data->file_data, tmp, len);
	data->file_len = len;
	if (close(fd) == -1)
		ft_error(7);
}

void	ft_check_len_file(t_desasm *data)
{
	unsigned int	aligned_name;
	unsigned int	aligned_comment;
	ssize_t			min_prog_len;

	aligned_name = PROG_NAME_LENGTH + 1;
	while ((aligned_name % 4) != 0)
		aligned_name++;
	aligned_comment = COMMENT_LENGTH + 1;
	while ((aligned_comment % 4) != 0)
		aligned_comment++;
	min_prog_len = 8 + aligned_name + aligned_comment + 2;
	if (data->file_len < min_prog_len)
		ft_error(8);
}

int		main(int argc, char **argv)
{
	t_desasm	*new;

	if (argc != 2)
		ft_error(1);
	new = (t_desasm*)malloc(sizeof(t_desasm));
	new->len_comands_code = 0;
	new->curent_position = 4;
	new->comands_list = NULL;
	ft_check_file_format(new, argv[1]);
	ft_open_read_close(new, argv[1]);
	ft_check_len_file(new);
	ft_valid_name_comment(new);
	dissassemble_comands(new);
	ft_create_file_and_write(new);
	return (0);
}

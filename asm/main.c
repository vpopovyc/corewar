#include "header.h"

void	ft_error(int n)
{
    ft_putstr("\033[0;31m");
    ft_putstr("ERROR\n");
    (n == 1) ? ft_putstr("Memory allocation error !\n") : 0;
   	(n == 2) ? ft_putstr("Wrong number of arguments !\n") : 0;
    (n == 3) ? ft_putstr("File doesn`t open, maybe wrong file name !\n") : 0;
    (n == 4) ? ft_putstr("It`s not possible to read the file !\n") : 0;
    (n == 5) ? ft_putstr("It`s not possible to close the file !\n") : 0;
    ft_putstr("USAGE: ./lem-in <mapfile name>\n");
    exit(-1);
}

void	ft_open(char *name, t_file *src)
{
	char s[2];

	((src->fd = open(name, O_RDONLY)) < 0) ? ft_error(3) : 0;
	(read(src->fd, s, 0) < 0) ? ft_error(4) : 0;
	(close(src->fd) < 0) ? ft_error(5) : 0;
	src->fd = open(name, O_RDONLY);
}

int		main(int argc, char **argv)
{
	t_file *new;

	(!(new = (t_file*)malloc(sizeof(t_file)))) ? ft_error(1) : 0;
	(argc != 2) ? ft_error(2) : ft_open(argv[1], new);

	return (0);
}

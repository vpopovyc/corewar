#include "header.h"

void	ft_error(int n)
{
//	ft_putstr("\033[0;31m");
	ft_putstr("ERROR\n");
	(n == 1) ? ft_putstr("Memory allocation error !\n") : 0;
   	(n == 2) ? ft_putstr("Wrong number of arguments !\n") : 0;
	(n == 3) ? ft_putstr("File doesn`t open, maybe wrong file name !\n") : 0;
	(n == 4) ? ft_putstr("It`s not possible to read the file !\n") : 0;
	(n == 5) ? ft_putstr("It`s not possible to close the file !\n") : 0;
	(n == 6) ? ft_putstr("Invalid header !\n") : 0;
	ft_putstr("USAGE: ./lem-in <mapfile name>\n\n");
	exit(-1);
}

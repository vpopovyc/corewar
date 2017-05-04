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
	(argc != 2) ? ft_error(2) : ft_open(argv[1], new);
	new->header = 0;
	new->name = NULL;
	new->comment = NULL;
	ft_validation(new);
	return (new);
}

int		main(int ac, char **av)
{
	t_gamer		*root;


	root = init_validation(ac, av);
	header_bc_init(&(root->header_bc), root->src);
	return (0);
}

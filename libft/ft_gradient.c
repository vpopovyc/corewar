/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gradient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 19:58:28 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/21 19:58:30 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fdf.h"

int		ft_gradient(int cl_str, int cl_end, t_ld *ld)
{
	int						res;
	static unsigned char	bt[7];
	static short			lt[3];
	static int				max;

	if (ld->cl_min == 0)
	{
		bt[0] = cl_str;
		bt[1] = cl_str >> 8;
		bt[2] = cl_str >> 16;
		bt[3] = cl_end;
		bt[4] = cl_end >> 8;
		bt[5] = cl_end >> 16;
		lt[0] = bt[0] - bt[3];
		lt[1] = bt[1] - bt[4];
		lt[2] = bt[2] - bt[5];
		max = ld->cl_max != 1 ? ld->cl_max - 1 : ld->cl_max;
	}
	res = 0;
	res += (bt[0] - lt[0] * ld->cl_min / max);
	res += (int)((bt[1] - lt[1] * ld->cl_min / max) << 8);
	res += (int)((bt[2] - lt[2] * ld->cl_min / max) << 16);
	return (res);
}

void	ft_init_help(t_root *root)
{
	void	*win;

	win = mlx_new_window(root->init, 250, 250, "help");
	mlx_string_put(root->init, win, 10, 0, 0xff0000, "'i' - create img");
	mlx_string_put(root->init, win, 10, 20, 0xff0000, "'d' - delete image");
	mlx_string_put(root->init, win, 10, 40, 0xff0000, "'-' - zoom out");
	mlx_string_put(root->init, win, 10, 60, 0xff0000, "'+' - zoom in");
	mlx_string_put(root->init, win, 10, 80, 0xff0000, "'z' - rotate x down");
	mlx_string_put(root->init, win, 10, 100, 0xff0000, "'x' - rotate x up");
	mlx_string_put(root->init, win, 10, 120, 0xff0000, "'c' - rotate y down");
	mlx_string_put(root->init, win, 10, 140, 0xff0000, "'v' - rotate y up");
	mlx_string_put(root->init, win, 10, 160, 0xff0000, "'b' - rotate z down");
	mlx_string_put(root->init, win, 10, 180, 0xff0000, "'n' - rotate z down");
	mlx_string_put(root->init, win, 10, 200, 0xff0000, "'0' add diag");
	mlx_string_put(root->init, win, 10, 220, 0xff0000, "'space' - kill pid");
}

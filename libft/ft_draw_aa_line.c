/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_aa_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 17:18:46 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/19 17:18:51 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fdf.h"

void	ft_i_put_pixel(t_root *root, int color, unsigned char opacity)
{
	*(root->i_data) = color;
	*(root->i_data + 1) = color >> 8;
	*(root->i_data + 2) = color >> 16;
	*(root->i_data + 3) = opacity;
}

void	ft_get_pixel_pos(int x, int y, t_root *root)
{
	if (x * 4 >= root->size_line || y >= root->w_h || x <= 0 || y <= 0)
		return ;
	root->i_data += (y * root->size_line) + (x * 4);
}

void	ft_x_move(t_root *root, t_ld *ld)
{
	if (ld->t_err + ld->dy < ld->de)
	{
		root->i_data = ld->t_i_data;
		ft_get_pixel_pos(ld->x0, ld->y0 + ld->sy, root);
		ft_i_put_pixel(root, ld->cl, 255 * (ld->t_err + ld->dy) / ld->de);
	}
	ld->err -= ld->dy;
	ld->x0 += ld->sx;
}

void	ft_y_move(t_root *root, t_ld *ld)
{
	if (ld->dx - ld->t_err < ld->de)
	{
		root->i_data = ld->t_i_data;
		ft_get_pixel_pos(ld->t_x0 + ld->sx, ld->y0, root);
		ft_i_put_pixel(root, ld->cl, 255 * (ld->dx - ld->t_err) / ld->de);
	}
	ld->err += ld->dx;
	ld->y0 += ld->sy;
}

void	ft_change_data(t_root *root, t_fdf *p_start, t_fdf *p_end)
{
	t_ld	ld;

	ft_get_ld(&ld, p_start, p_end, root);
	while (ld.x0 != ld.x1 || ld.y0 != ld.y1)
	{
		root->i_data = ld.t_i_data;
		ft_get_pixel_pos(ld.x0, ld.y0, root);
		ld.cl = ft_gradient(p_start->color, p_end->color, &ld);
		ft_i_put_pixel(root, ld.cl, 255 * abs(ld.err - ld.dx + ld.dy) / ld.de);
		ld.t_err = ld.err;
		ld.t_x0 = ld.x0;
		ld.t_err << 1 >= -ld.dx ? ft_x_move(root, &ld) : 0;
		ld.t_err << 1 <= ld.dy ? ft_y_move(root, &ld) : 0;
		++ld.cl_min;
	}
	root->i_data = ld.t_i_data;
}

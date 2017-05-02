/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawpixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:18:46 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/23 14:50:51 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fdf.h"

void	ft_p_move_lr_ud(t_root *root, int *x, int *y, int *z)
{
	*x += root->move_r - root->move_l;
	*y += root->move_u - root->move_d;
	*z += root->move_r - root->move_l;
}

void	ft_p_modify_x(int *y, int *z, t_root *root)
{
	double	ty;
	double	tz;

	ty = *y;
	tz = *z;
	*y = ty * cos(root->x_an * M_PI_180) + tz * sin(root->x_an * M_PI_180);
	*z = tz * cos(root->x_an * M_PI_180) - ty * sin(root->x_an * M_PI_180);
}

void	ft_p_modify_y(int *x, int *z, t_root *root)
{
	double	tx;
	double	tz;

	tx = *x;
	tz = *z;
	*x = tx * cos(root->y_an * M_PI_180) + tz * sin(root->y_an * M_PI_180);
	*z = tz * cos(root->y_an * M_PI_180) - tx * sin(root->y_an * M_PI_180);
}

void	ft_p_modify_z(int *x, int *y, t_root *root)
{
	double	tx;
	double	ty;

	tx = *x;
	ty = *y;
	*x = tx * cos(root->z_an * M_PI_180) + ty * sin(root->z_an * M_PI_180);
	*y = ty * cos(root->z_an * M_PI_180) - tx * sin(root->z_an * M_PI_180);
}

void	ft_drawpixel(t_root *root, t_fdf *pixel)
{
	char	*i_tmp;
	int		x;
	int		y;
	int		z;

	x = (pixel->c_x - root->x_md) * root->mult;
	y = (pixel->c_y - root->y_md) * root->mult;
	z = pixel->c_z * root->mult;
	ft_p_modify_x(&y, &z, root);
	ft_p_modify_y(&x, &z, root);
	ft_p_modify_z(&x, &y, root);
	ft_p_move_lr_ud(root, &x, &y, &z);
	i_tmp = root->i_data;
	ft_get_pixel_pos(x, y, root);
	ft_i_put_pixel(root, pixel->color, 0);
	root->i_data = i_tmp;
}

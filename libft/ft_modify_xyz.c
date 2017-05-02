/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modify_xyz.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 16:58:51 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/26 16:58:54 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fdf.h"

void		ft_move_lr_ud(t_root *root, t_ld *ld)
{
	ld->x0 += root->move_r - root->move_l;
	ld->y0 += root->move_u - root->move_d;
	ld->x1 += root->move_r - root->move_l;
	ld->y1 += root->move_u - root->move_d;
	ld->z0 += root->move_r - root->move_l;
	ld->z1 += root->move_u - root->move_d;
}

void		ft_modify_x(t_root *root, t_ld *ld)
{
	double y;
	double z;

	y = ld->y0;
	z = ld->z0;
	ld->y0 = y * cos(root->x_an * M_PI_180) + z * sin(root->x_an * M_PI_180);
	ld->z0 = z * cos(root->x_an * M_PI_180) - y * sin(root->x_an * M_PI_180);
	y = ld->y1;
	z = ld->z1;
	ld->y1 = y * cos(root->x_an * M_PI_180) + z * sin(root->x_an * M_PI_180);
	ld->z1 = z * cos(root->x_an * M_PI_180) - y * sin(root->x_an * M_PI_180);
}

void		ft_modify_y(t_root *root, t_ld *ld)
{
	double x;
	double z;

	x = ld->x0;
	z = ld->z0;
	ld->x0 = x * cos(root->y_an * M_PI_180) + z * sin(root->y_an * M_PI_180);
	ld->z0 = z * cos(root->y_an * M_PI_180) - x * sin(root->y_an * M_PI_180);
	x = ld->x1;
	z = ld->z1;
	ld->x1 = x * cos(root->y_an * M_PI_180) + z * sin(root->y_an * M_PI_180);
	ld->z1 = z * cos(root->y_an * M_PI_180) - x * sin(root->y_an * M_PI_180);
}

void		ft_modify_z(t_root *root, t_ld *ld)
{
	double y;
	double x;

	x = ld->x0;
	y = ld->y0;
	ld->x0 = x * cos(root->z_an * M_PI_180) + y * sin(root->z_an * M_PI_180);
	ld->y0 = y * cos(root->z_an * M_PI_180) - x * sin(root->z_an * M_PI_180);
	x = ld->x1;
	y = ld->y1;
	ld->x1 = x * cos(root->z_an * M_PI_180) + y * sin(root->z_an * M_PI_180);
	ld->y1 = y * cos(root->z_an * M_PI_180) - x * sin(root->z_an * M_PI_180);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 17:11:36 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/08 21:24:16 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fdf.h"

void	ft_merge(t_fdf **up, t_fdf **down)
{
	t_fdf	*head;
	t_fdf	*tail;

	head = *up;
	tail = *down;
	while (*up)
	{
		(*up)->down = *down;
		*up = (*up)->right;
		*down = (*down)->right;
	}
	*up = head;
	*down = tail;
}

void	ft_mod_cord(t_fdf *node, int x, int y, int z)
{
	node->c_x = x;
	node->c_y = y;
	node->c_z = z;
}

void	ft_get_root(int def_color, int err_color, t_root *new)
{
	new->def_color = def_color;
	new->err_color = err_color;
	new->head = NULL;
	new->x_max = 0;
	new->status = 0;
	new->w_h = 1000;
	new->w_w = 1500;
	new->mult = 1;
	new->move_d = 0;
	new->move_u = 0;
	new->move_l = 0;
	new->move_r = 0;
	new->x_an = 0;
	new->y_an = 00;
	new->z_an = 0;
	new->display_diag = 0;
}

void	ft_get_ld(t_ld *ld, t_fdf *p_start, t_fdf *p_end, t_root *root)
{
	ld->x0 = (p_start->c_x - root->x_md) * root->mult;
	ld->y0 = (p_start->c_y - root->y_md) * root->mult;
	ld->x1 = (p_end->c_x - root->x_md) * root->mult;
	ld->y1 = (p_end->c_y - root->y_md) * root->mult;
	ld->z0 = p_start->c_z * root->mult;
	ld->z1 = p_end->c_z * root->mult;
	ft_modify_x(root, ld);
	ft_modify_y(root, ld);
	ft_modify_z(root, ld);
	ft_move_lr_ud(root, ld);
	ld->sx = ld->x0 < ld->x1 ? 1 : -1;
	ld->sy = ld->y0 < ld->y1 ? 1 : -1;
	ld->dx = abs(ld->x1 - ld->x0);
	ld->dy = abs(ld->y1 - ld->y0);
	ld->de = ld->dx + ld->dy == 0 ? 1 : sqrt(ld->dx * ld->dx + ld->dy * ld->dy);
	ld->err = ld->dx - ld->dy;
	ld->t_i_data = root->i_data;
	ld->cl_min = 0;
	ld->cl_max = ld->dx >= ld->dy ? ld->dx : ld->dy;
}

t_fdf	*ft_new_node(int y, int x, int z, int color)
{
	t_fdf	*new;

	new = (t_fdf*)malloc(sizeof(t_fdf));
	new->c_x = x;
	new->c_y = y;
	new->c_z = z;
	new->color = color;
	new->right = NULL;
	new->down = NULL;
	new->diag = NULL;
	return (new);
}

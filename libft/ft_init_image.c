/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 15:23:01 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/16 15:23:03 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_fdf.h"

void	ft_rec(t_root *root, t_fdf *head, t_fdf *draw)
{
	if (draw->right == NULL && draw->down == NULL && draw->diag == NULL)
		return (ft_drawpixel(root, draw));
	if (draw->right != NULL)
		ft_rec(root, head, draw->right);
	else if (draw->right == NULL && draw->down != NULL)
		ft_rec(root, head->down, head->down);
	if (draw->right != NULL)
		ft_change_data(root, draw, draw->right);
	if (draw->diag != NULL && root->display_diag)
		ft_change_data(root, draw, draw->diag);
	if (draw->down != NULL)
		ft_change_data(root, draw, draw->down);
}

void	ft_fill_image(t_root *root)
{
	t_fdf	*head;
	t_fdf	*draw;

	head = root->head;
	draw = head;
	root->x_md = (root->x_max + root->head->c_x) / 2;
	root->y_md = (root->y_max + root->head->c_y) / 2;
	if (draw != NULL)
		ft_rec(root, head, draw);
}

int		ft_image(t_root *root)
{
	int		bpp;
	int		en;

	root->img = mlx_new_image(root->init, root->w_w, root->w_h);
	root->i_data = mlx_get_data_addr(root->img, &bpp, &root->size_line, &en);
	ft_fill_image(root);
	return (1);
}

int		ft_key_hook(int kc, t_root *root)
{
	if (kc == 53 || kc == 49 || kc == 34 || kc == 2 || kc == 24 || kc == 27)
		ft_matrix_control(kc, root);
	else if (kc == 125 || kc == 126 || kc == 124 || kc == 123 || kc == 82)
		ft_keycode_moves(kc, root);
	else if (kc == 6 || kc == 7 || kc == 8 || kc == 9 || kc == 11 || kc == 45)
		ft_keycode_angle(kc, root);
	else if (kc == 4)
		ft_init_help(root);
	return (0);
}

int		ft_init_image(t_root *root)
{
	root->init = mlx_init();
	if (root->init == NULL)
		exit(ft_printf("Couldn't establish connection\n"));
	root->win = mlx_new_window(root->init, root->w_w, root->w_h, "fil de fer");
	if (root->win == NULL)
		exit(ft_printf("Couldn't create window\n"));
	root->status = 0;
	mlx_hook(root->win, 2, 5, ft_key_hook, root);
	mlx_loop(root->init);
	return (0);
}

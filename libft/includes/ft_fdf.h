/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:51:56 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/02/10 15:04:07 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_FDF_H
# define __FT_FDF_H

# include "libft.h"

typedef	struct		s_fdf
{
	int				c_x;
	int				c_y;
	int				c_z;
	int				color;
	struct s_fdf	*right;
	struct s_fdf	*diag;
	struct s_fdf	*down;
}					t_fdf;

typedef	struct		s_root
{
	int				def_color;
	int				err_color;
	int				y_max;
	int				x_max;
	unsigned char	status;
	void			*init;
	void			*win;
	void			*img;
	char			*i_data;
	int				size_line;
	int				w_h;
	int				w_w;
	int				mult;
	int				x_md;
	int				y_md;
	int				move_u;
	int				move_d;
	int				move_r;
	int				move_l;
	int				x_an;
	int				y_an;
	int				z_an;
	char			display_diag;
	struct s_fdf	*head;
}					t_root;

typedef	struct		s_ld
{
	int		x0;
	int		x1;
	int		y0;
	int		y1;
	int		z0;
	int		z1;
	int		sx;
	int		sy;
	int		dx;
	int		dy;
	int		de;
	int		err;
	int		t_err;
	int		t_x0;
	int		cl;
	int		cl_min;
	int		cl_max;
	char	*t_i_data;
}					t_ld;

void				ft_fdf(char *av);
void				ft_init_help(t_root *root);
void				ft_keycode_angle(int keycode, t_root *root);
void				ft_keycode_moves(int keycode, t_root *root);
void				ft_matrix_control(int keycode, t_root *root);
void				ft_kittens_killa(t_root *root);
void				ft_multiply(t_root *root, int keycode);
void				ft_move_lr_ud(t_root *root, t_ld *ld);
void				ft_modify_x(t_root *root, t_ld *ld);
void				ft_modify_y(t_root *root, t_ld *ld);
void				ft_modify_z(t_root *root, t_ld *ld);
void				ft_p_modify_x(int *y, int *z, t_root *root);
void				ft_p_modify_y(int *x, int *z, t_root *root);
void				ft_p_modify_z(int *x, int *y, t_root *root);
void				ft_p_move_lr_ud(t_root *root, int *x, int *y, int *z);
void				ft_drawpixel(t_root *root, t_fdf *pixel);
int					ft_image(t_root *root);
int					ft_init_image(t_root *root);
void				ft_fill_image(t_root *root);
int					ft_key_hook(int keycode, t_root *root);
void				ft_rec(t_root *root, t_fdf *head, t_fdf *draw);
void				ft_i_put_pixel(t_root *root, int color,
								unsigned char opacity);
void				ft_get_pixel_pos(int x, int y, t_root *root);
void				ft_x_move(t_root *root, t_ld *ld);
void				ft_y_move(t_root *root, t_ld *ld);
void				ft_change_data(t_root *root, t_fdf *p_start, t_fdf *p_end);
int					ft_gradient(int cl_str, int cl_end, t_ld *ld);
void				ft_mod_cord(t_fdf *node, int x, int y, int z);
t_fdf				*ft_new_node(int x, int y, int z, int color);
void				ft_merge(t_fdf **up, t_fdf **down);
void				ft_get_root(int def_color, int err_color, t_root *new);
void				ft_get_ld(t_ld *ld, t_fdf *p_start,
							t_fdf *p_end, t_root *root);
void				ft_diagonal(t_root *root);
void				ft_color(t_root *root, char **line, t_fdf **node);
t_fdf				*ft_loop(char *line, int n, t_root *root);
void				ft_spc(int *x, char *f, t_fdf **head, t_fdf **node);
int					ft_parse(int fd, t_root *root);
#endif

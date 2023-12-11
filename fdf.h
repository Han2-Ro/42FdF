/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:37:08 by hrother           #+#    #+#             */
/*   Updated: 2023/12/11 22:12:14 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

# define HEIGHT 900
# define WIDTH 1000
# define HEX "0123456789abcdef"

typedef struct t_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

typedef struct s_perspective
{
	float	x_trans;
	float	y_trans;
	float	z_rot;
	float	x_rot;
	float	zoom;
}	t_perspective;

typedef struct s_map
{
	float	**height;
	int		**color;
	int		x_size;
	int		y_size;
}	t_map;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_img			*img;
	t_map			*map;
	t_perspective	pers;
}	t_vars;

void	put_pixel(t_img *data, int x, int y, int color);
void	draw_line(t_point start, t_point end, t_img *data);
t_point	init_point(float x, float y, float z, int color);
int		on_keypress(int keycode, t_vars *vars);
t_map	*init_map(char *filename);
void	draw_map(t_map *map, t_img *img, t_perspective pers);
t_point	apply_pers(t_point point, t_perspective pers);
void	print_map(t_map map);
void	free_strs(char **arr);
int		count_w(char const *s, char c);
int		ft_atoi_base(char *str, const char *base);

#endif
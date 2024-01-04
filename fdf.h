/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:37:08 by hrother           #+#    #+#             */
/*   Updated: 2024/01/04 11:46:39 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>

# define HEIGHT 900
# define WIDTH 1000
# define HEX "0123456789abcdef"
# define ROT_ANGLE 0.392699082f
# define BUFFER_SIZE 5000
# define COLORED 1

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
	float	z_trans;
	float	z_rot;
	float	x_rot;
	float	zoom;
	float	z_scale;
	int		isoemtric;
}	t_pers;

typedef struct s_map
{
	float	**height;
	int		**color;
	int		x_size;
	int		y_size;
}	t_map;

typedef struct s_key
{
	int		keycode;
	int		pressed;
	float	dif;
	float	*val;
}	t_key;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_map	*map;
	t_key	*keys;
	t_pers	pers;
}	t_vars;

typedef struct s_line_data
{
	int	dx;
	int	dy;
	int	step_x;
	int	step_y;
	int	swap;
	int	x;
	int	y;
	int	error;
}	t_line_data;

void	put_pixel(t_img *data, int x, int y, int color);
void	draw_line(t_point start, t_point end, t_img *data);
t_point	init_point(float x, float y, float z, int color);
int		on_keypress(int keycode, t_vars *vars);
t_map	*init_map(const char *filename);
void	draw_map(t_map *map, t_img *img, t_pers pers);
t_point	*apply_pers(t_point *point, t_pers pers);
void	print_map(t_map map);
void	free_strs(char **arr);
int		count_w(char const *s, char c);
int		ft_atoi_base(char *str, const char *base);
int		close_win(t_vars *vars);
void	set_starting_pers(t_vars *vars);
int		min(int a, int b);
int		on_keypressed(int keycode, t_vars *vars);
int		on_keyreleased(int keycode, t_vars *vars);
int		on_loop(t_vars *vars);
t_key	*init_keys(t_vars *vars);
void	apply_all_keys(float deltatime, t_vars *vars);
int		set_key(int keycode, int state, t_vars *vars);

#endif
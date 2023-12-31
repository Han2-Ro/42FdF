/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:37:08 by hrother           #+#    #+#             */
/*   Updated: 2024/01/06 19:03:50 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
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
	float	focal_length;
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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_key	*keys;
	t_img	img;
	t_pers	pers;
}	t_data;

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

t_point	*transform(t_point *point, t_pers pers);
void	draw_line(t_point start, t_point end, t_img img);
void	draw_map(t_data *data);

t_map	*init_map(const char *filename);

t_key	*init_keys(t_data *data);
void	apply_all_keys(float deltatime, t_data *data);
int		set_key(int keycode, int state, t_data *data);

void	free_map(t_map *map);
int		close_win(t_data *data);
int		on_keypressed(int keycode, t_data *data);
int		on_keyreleased(int keycode, t_data *data);
int		on_loop(t_data *data);

void	free_strs(char **arr);
int		count_w(char const *s, char c);
int		ft_atoi_base(char *str, const char *base);
int		min(int a, int b);
t_point	init_point(t_data *data, int x, int y);

#endif
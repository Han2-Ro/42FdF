/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:37:08 by hrother           #+#    #+#             */
/*   Updated: 2023/12/09 19:15:42 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>

# define HEIGHT 720
# define WIDTH 1280

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

void	put_pixel(t_data *data, t_point pixel);
int		close(int keycode, t_vars *vars);
void	draw_line(t_point start, t_point end, t_data *data);
t_point init_point(int x, int y, int color);

#endif
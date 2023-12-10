/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:34:33 by hrother           #+#    #+#             */
/*   Updated: 2023/12/10 22:05:17 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	line_across_x(t_point start, int d_x, int d_y, t_data *data)
{
	int		direction;
	int		i;
	t_point	pixel;

	pixel.color = start.color;
	if (d_x > 0)
		direction = 1;
	else
		direction = -1;
	i = 0;
	while (i <= d_x * direction)
	{
		pixel.x = start.x + i * direction;
		pixel.y = start.y + i * d_y / (d_x * direction);
		put_pixel(data, (int)pixel.x, (int)pixel.y, pixel.color);
		i++;
	}
}

void	line_across_y(t_point start, int d_x, int d_y, t_data *data)
{
	//TODO: consider using bresenham's line drawing algorithm
	int		direction;
	int		i;
	t_point	pixel;

	pixel.color = start.color;
	if (d_y > 0)
		direction = 1;
	else
		direction = -1;
	i = 0;
	while (i <= d_y * direction)
	{
		pixel.y = start.y + i * direction;
		pixel.x = start.x + i * d_x / (d_y * direction);
		put_pixel(data, (int)pixel.x, (int)pixel.y, pixel.color);
		i++;
	}
}

void	draw_line(t_point start, t_point end, t_data *img)
{
	int		d_x;
	int		d_y;

	d_x = end.x - start.x;
	d_y = end.y - start.y;
	if (d_x == 0 && d_y == 0)
		return ;
	if (fabs((double) d_x) > fabs((double) d_y))
		line_across_x(start, d_x, d_y, img);
	else
		line_across_y(start, d_x, d_y, img);
}

t_point	conv_cosy(t_point point)
{
	point.x = (point.x + 3) * 100;
	point.y = (point.y + 3) * 100;
	point.z = (point.z + 3) * 100;
	return (point);
}

void	draw_map(t_map *map, t_data *img, t_perspective pers)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			p1 = init_point(x, y, map->arr[y][x], 0x0000FFFF);
			p1 = conv_cosy(apply_pers(p1, pers));
			if (x + 1 < map->x_size)
			{
				p2 = init_point(x + 1, y, map->arr[y][x + 1], 0x0000FFFF);
				p2 = conv_cosy(apply_pers(p2, pers));
				draw_line(p1, p2, img);
			}
			if (y + 1 < map->y_size)
			{
				p2 = init_point(x, y + 1, map->arr[y + 1][x], 0x0000FFFF);
				p2 = conv_cosy(apply_pers(p2, pers));
				draw_line(p1, p2, img);
			}
			x++;
		}
		y++;
	}
}

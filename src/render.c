/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:34:33 by hrother           #+#    #+#             */
/*   Updated: 2023/12/12 21:28:33 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	blend_bytes(int a, int b, float f, int mask)
{
	int	res;

	a = a & mask;
	b = b & mask;
	res = a * (1.0f - f) + b * f;
	return (res & mask);
}

int	blend(int a, int b, float f)
{
	int	res;

	res = blend_bytes(a, b, f, 0xff000000);
	res = res | blend_bytes(a, b, f, 0xff0000);
	res = res | blend_bytes(a, b, f, 0xff00);
	res = res | blend_bytes(a, b, f, 0xff);
	return (res);
}

/*
int	main(void)
{
	float f;
	f = 0;
	while (f <= 1)
	{
		printf("%f %x\n", f, blend(0xff, 0xff00, f));
		f += 0.05f;
	}
	return 0;
}
*/

void	line_across_x(t_point start, t_point end, int d_x, int d_y, t_img *data)
{
	float		direction;
	float		i;
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
		pixel.color = blend(start.color, end.color, (i + .0f) / (d_x * direction));
		put_pixel(data, (int)pixel.x, (int)pixel.y,  pixel.color);
		i++;
	}
}

void	line_across_y(t_point start, t_point end, int d_x, int d_y, t_img *data)
{
	//TODO: consider using bresenham's line drawing algorithm
	float		direction;
	float		i;
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
		pixel.color = blend(start.color, end.color, i / (d_y * direction));
		put_pixel(data, (int)pixel.x, (int)pixel.y, pixel.color);
		i++;
	}
}

void	draw_line(t_point start, t_point end, t_img *img)
{
	int		d_x;
	int		d_y;

	d_x = end.x - start.x;
	d_y = end.y - start.y;
	if (d_x == 0 && d_y == 0)
		return ;
	if (fabs((double) d_x) > fabs((double) d_y))
		line_across_x(start, end, d_x, d_y, img);
	else
		line_across_y(start, end, d_x, d_y, img);
}

t_point	conv_cosy(t_point point)
{
	point.x = point.x * 20 + WIDTH / 2;
	point.y = point.y * 20 + HEIGHT / 2;
	point.z = point.z * 20 + HEIGHT / 2;
	//point.z = (point.z + 3) * 100;
	return (point);
}

void	draw_map(t_map *map, t_img *img, t_perspective pers)
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
			p1 = init_point(x, y, map->height[y][x], map->color[y][x]);
			p1 = conv_cosy(apply_pers(p1, pers));
			if (x + 1 < map->x_size)
			{
				p2 = init_point(x + 1, y, map->height[y][x + 1], map->color[y][x + 1]);
				p2 = conv_cosy(apply_pers(p2, pers));
				draw_line(p1, p2, img);
			}
			if (y + 1 < map->y_size)
			{
				p2 = init_point(x, y + 1, map->height[y + 1][x], map->color[y + 1][x]);
				p2 = conv_cosy(apply_pers(p2, pers));
				draw_line(p1, p2, img);
			}
			x++;
		}
		y++;
	}
}

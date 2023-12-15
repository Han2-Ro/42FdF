/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:34:33 by hrother           #+#    #+#             */
/*   Updated: 2023/12/15 18:22:26 by hannes           ###   ########.fr       */
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
	float	direction;
	float	i;
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
		(void)end;
		pixel.color = blend(start.color, end.color, (i + .0f) / (d_x * direction));
		put_pixel(data, (int)pixel.x, (int)pixel.y,  pixel.color);
		i++;
	}
}

void	line_across_y(t_point start, t_point end, int d_x, int d_y, t_img *data)
{
	float	direction;
	float	i;
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
		(void)end;
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

t_point	*conv_cosy(t_point *point)
{
	if (point)
	{
		point->x += WIDTH / 2;
		point->y += HEIGHT / 2;
		point->z += HEIGHT / 2;
	}
	return (point);
}

void	draw_lines_from(t_map *map, t_img *img, int x, int y, t_perspective pers)
{
	t_point	point[2];
	t_point	*ptr[2];
	
	point[0] = init_point(x, y, map->height[y][x], map->color[y][x]);
	ptr[0] = conv_cosy(apply_pers(point, pers));
	if (x + 1 < map->x_size)
	{
		point[1] = init_point(x + 1, y, map->height[y][x + 1], map->color[y][x + 1]);
		ptr[1] = conv_cosy(apply_pers(point + 1, pers));
		if (ptr[0] && ptr[1])
			draw_line(*ptr[0], *ptr[1], img);
	}
	if (y + 1 < map->y_size)
	{
		point[1] = init_point(x, y + 1, map->height[y + 1][x], map->color[y + 1][x]);
		ptr[1] = conv_cosy(apply_pers(point + 1, pers));
		if (ptr[0] != 0 && ptr[1] != 0)
			draw_line(*ptr[0], *ptr[1], img);
	}
}

void	draw_map(t_map *map, t_img *img, t_perspective pers)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			draw_lines_from(map, img, x, y, pers);
			x++;
		}
		y++;
	}
}

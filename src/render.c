/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:34:33 by hrother           #+#    #+#             */
/*   Updated: 2024/01/02 20:23:50 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

void	draw_lines_from(t_map *map, t_img *img, int x, int y, t_pers pers)
{
	t_point	point[2];
	t_point	*ptr[2];

	point[0] = init_point(x, y, map->height[y][x], map->color[y][x]);
	ptr[0] = conv_cosy(apply_pers(point, pers));
	if (x + 1 < map->x_size)
	{
		point[1] = init_point(
				x + 1, y,
				map->height[y][x + 1],
				map->color[y][x + 1]);
		ptr[1] = conv_cosy(apply_pers(point + 1, pers));
		if (ptr[0] && ptr[1])
			draw_line(*ptr[0], *ptr[1], img);
	}
	if (y + 1 < map->y_size)
	{
		point[1] = init_point(
				x, y + 1,
				map->height[y + 1][x],
				map->color[y + 1][x]);
		ptr[1] = conv_cosy(apply_pers(point + 1, pers));
		if (ptr[0] != 0 && ptr[1] != 0)
			draw_line(*ptr[0], *ptr[1], img);
	}
}

void	draw_map(t_map *map, t_img *img, t_pers pers)
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

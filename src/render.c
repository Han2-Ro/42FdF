/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:34:33 by hrother           #+#    #+#             */
/*   Updated: 2024/01/06 14:07:25 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

void	draw_lines_from(t_vars *vars, int x, int y)
{
	t_point	point[2];
	t_point	*ptr[2];

	point[0] = init_point(x, y, vars->map->height[y][x], vars->map->color[y][x]);
	ptr[0] = conv_cosy(transform(point, vars->pers));
	if (x + 1 < vars->map->x_size)
	{
		point[1] = init_point(
				x + 1, y,
				vars->map->height[y][x + 1],
				vars->map->color[y][x + 1]);
		ptr[1] = conv_cosy(transform(point + 1, vars->pers));
		if (ptr[0] && ptr[1])
			draw_line(*ptr[0], *ptr[1], vars->img);
	}
	if (y + 1 < vars->map->y_size)
	{
		point[1] = init_point(
				x, y + 1,
				vars->map->height[y + 1][x],
				vars->map->color[y + 1][x]);
		ptr[1] = conv_cosy(transform(point + 1, vars->pers));
		if (ptr[0] != 0 && ptr[1] != 0)
			draw_line(*ptr[0], *ptr[1], vars->img);
	}
}

void	draw_map(t_vars *vars)
{
	int		x;
	int		y;

	y = 0;
	while (y < vars->map->y_size)
	{
		x = 0;
		while (x < vars->map->x_size)
		{
			draw_lines_from(vars, x, y);
			x++;
		}
		y++;
	}
}

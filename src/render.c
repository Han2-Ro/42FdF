/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:34:33 by hrother           #+#    #+#             */
/*   Updated: 2024/01/06 14:39:33 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_point	*conic_projection(t_point *point, float f, float d_cam)
{
	float	z;

	z = d_cam - point->z;
	if (z <= 10)
		return (NULL);
	point->x = point->x * f / z;
	point->y = point->y * f / z;
	return (point);
}

t_point	*apply_pers(t_point *point, t_pers pers)
{
	transform(point, pers);
	if (!pers.isoemtric)
		point = conic_projection(point, 600.0f, 300);
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

	point[0] = init_point(vars, x, y);
	ptr[0] = apply_pers(point, vars->pers);
	if (x + 1 < vars->map->x_size)
	{
		point[1] = init_point(vars, x + 1, y);
		ptr[1] = apply_pers(point + 1, vars->pers);
		if (ptr[0] && ptr[1])
			draw_line(*ptr[0], *ptr[1], vars->img);
	}
	if (y + 1 < vars->map->y_size)
	{
		point[1] = init_point(vars, x, y + 1);
		ptr[1] = apply_pers(point + 1, vars->pers);
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

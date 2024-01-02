/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:25:17 by hrother           #+#    #+#             */
/*   Updated: 2024/01/02 20:12:29 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_point	*rotate_z(t_point *point, float angle)
{
	t_point	tmp;

	tmp = *point;
	point->x = tmp.x * cos(angle) - tmp.y * sin(angle);
	point->y = tmp.x * sin(angle) + tmp.y * cos(angle);
	return (point);
}

t_point	*rotate_x(t_point *point, float angle)
{
	t_point	tmp;

	tmp = *point;
	point->y = tmp.y * cos(angle) - tmp.z * sin(angle);
	point->z = tmp.y * sin(angle) + tmp.z * cos(angle);
	return (point);
}

t_point	*scale(t_point *point, float factor)
{
	point->x *= factor;
	point->y *= factor;
	point->z *= factor;
	return (point);
}

t_point	*translate(t_point *point, float x, float y, float z)
{
	point->x += x;
	point->y += y;
	point->z += z;
	return (point);
}

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
	translate(point, pers.x_trans, pers.y_trans, pers.z_trans);
	scale(point, pers.zoom);
	point->z = point->z * pers.z_scale;
	rotate_z(point, pers.z_rot);
	rotate_x(point, pers.x_rot);
	if (!pers.isoemtric)
		point = conic_projection(point, 600.0f, 300);
	return (point);
}

void	set_starting_pers(t_vars *vars)
{
	int	max_map_dim;

	max_map_dim = vars->map->x_size;
	if (vars->map->y_size > max_map_dim)
		max_map_dim = vars->map->y_size;
	vars->pers.zoom = min(HEIGHT, WIDTH) / 1.5 / max_map_dim;
	vars->pers.y_trans = vars->map->y_size / -2;
	vars->pers.x_trans = vars->map->x_size / -2;
	vars->pers.z_trans = 0;
	vars->pers.z_rot = -1 * ROT_ANGLE;
	vars->pers.x_rot = 1 * ROT_ANGLE;
	vars->pers.z_scale = 0.5f;
	vars->pers.isoemtric = 1;
}

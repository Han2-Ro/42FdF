/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:25:17 by hrother           #+#    #+#             */
/*   Updated: 2024/01/06 14:37:10 by hannes           ###   ########.fr       */
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

t_point	*transform(t_point *point, t_pers pers)
{
	translate(point, pers.x_trans, pers.y_trans, pers.z_trans);
	scale(point, pers.zoom);
	point->z = point->z * pers.z_scale;
	rotate_z(point, pers.z_rot);
	rotate_x(point, pers.x_rot);
	return (point);
}

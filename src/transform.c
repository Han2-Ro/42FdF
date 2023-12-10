/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:25:17 by hrother           #+#    #+#             */
/*   Updated: 2023/12/11 00:40:55 by hannes           ###   ########.fr       */
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

t_point	*translate(t_point *point, float x, float y)
{
	point->x += x;
	point->y += y;
	return (point);
}

t_point	apply_pers(t_point point, t_perspective pers)
{
	translate(&point, pers.x_trans, pers.y_trans);
	scale(&point, pers.zoom);
	rotate_z(&point, pers.z_rot);
	rotate_x(&point, pers.x_rot);
	return (point);
}

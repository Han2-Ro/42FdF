/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:25:17 by hrother           #+#    #+#             */
/*   Updated: 2023/12/10 17:00:09 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_point	rotate_z(t_point point, float angle)
{
	t_point res;

	res.color = point.color;
	res.x = point.x * cos(angle) - point.y * sin(angle);
	res.y = point.x * sin(angle) + point.y * cos(angle);
	res.z = point.z;
	return (res);
}

t_point	rotate_x(t_point point, float angle)
{
	t_point res;

	res.color = point.color;
	res.x = point.x;
	res.y = point.y * cos(angle) - point.z * sin(angle);
	res.z = point.y * sin(angle) + point.z * cos(angle);
	return (res);
}

t_point	apply_pers(t_point point, t_perspective pers)
{
	return (rotate_x(rotate_z(point, pers.z_rot), pers.x_rot));
}

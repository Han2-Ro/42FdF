/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:38:04 by hrother           #+#    #+#             */
/*   Updated: 2023/12/09 21:08:29 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel(t_data *data, t_point pixel)
{
	char	*dst;

	dst = data->addr + (pixel.y * data->line_length + pixel.x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = pixel.color;
}

t_point init_point(int x, int y, int color)
{
	t_point point;
	
	point.x = x;
	point.y = y;
	point.color = color;
	return (point);
}

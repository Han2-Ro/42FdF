/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:38:04 by hrother           #+#    #+#             */
/*   Updated: 2023/12/09 19:16:09 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel(t_data *data, t_point pixel)
{
	char	*dst;

	dst = data->addr + (pixel.y * data->line_length + pixel.x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = pixel.color;
}

int	close(int keycode, t_vars *vars)
{
	(void) keycode;
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

t_point init_point(int x, int y, int color)
{
	t_point point;
	
	point.x = x;
	point.y = y;
	point.color = color;
	return (point);
}

void	draw_line(t_point start, t_point end, t_data *data)
{
	int		d_x;
	int		d_y;
	t_point	pixel;
	int		i;/* code */
	int		direction;

	d_x = end.x - start.x;
	d_y = end.y - start.y;
	pixel.color = start.color;
	pixel.x = start.x;
	i = 0;
	if (d_x > d_y)
	{
		if (d_x > 0)
			direction = 1;
		else
			direction = -1;
		while (i * direction <= d_x)
		{
			pixel.x = start.x + i * direction;
			pixel.y = start.y + i * d_x / d_y;
			put_pixel(data, pixel);
			i++;
		}
	}
}

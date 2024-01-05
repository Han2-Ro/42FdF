/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:57:55 by hannes            #+#    #+#             */
/*   Updated: 2024/01/05 23:54:47 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel(t_img data, int x, int y, int color)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return ;
	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

t_line_data	set_line_data(t_point start, t_point end)
{
	t_line_data	data;
	int			temp;

	data.dx = end.x - start.x;
	data.dy = end.y - start.y;
	data.step_x = 1;
	if (data.dx < 0)
		data.step_x = -1;
	data.step_y = 1;
	if (data.dy < 0)
		data.step_y = -1;
	data.dx = abs(data.dx);
	data.dy = abs(data.dy);
	data.swap = 0;
	if (data.dy > data.dx)
	{
		data.swap = 1;
		temp = data.dx;
		data.dx = data.dy;
		data.dy = temp;
	}
	data.x = start.x;
	data.y = start.y;
	data.error = 2 * data.dy - data.dx;
	return (data);
}

void	draw_line(t_point start, t_point end, t_img img)
{
	t_line_data	data;
	int			i;
	int			color;

	data = set_line_data(start, end);
	i = 0;
	while (i <= data.dx)
	{
		color = blend(start.color, end.color, (float)i / data.dx);
		put_pixel(img, (int)data.x, (int)data.y, color);
		if (data.error > 0)
		{
			if (data.swap)
				data.x += data.step_x;
			else
				data.y += data.step_y;
			data.error -= 2 * data.dx;
		}
		if (data.swap)
			data.y += data.step_y;
		else
			data.x += data.step_x;
		data.error += 2 * data.dy;
		i++;
	}
}

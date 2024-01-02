/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:57:55 by hannes            #+#    #+#             */
/*   Updated: 2024/01/02 20:24:39 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

//TODO: bresenhams line algorithm
void	line_across_x(t_point start, t_point end, int d_x, int d_y, t_img *data)
{
	float	direction;
	float	i;
	t_point	pixel;

	pixel.color = start.color;
	if (d_x > 0)
		direction = 1;
	else
		direction = -1;
	i = 0;
	while (i <= d_x * direction)
	{
		pixel.x = start.x + i * direction;
		pixel.y = start.y + i * d_y / (d_x * direction);
		(void)end;
		pixel.color = blend(
				start.color,
				end.color,
				(i + .0f) / (d_x * direction));
		put_pixel(data, (int)pixel.x, (int)pixel.y, pixel.color);
		i++;
	}
}

void	line_across_y(t_point start, t_point end, int d_x, int d_y, t_img *data)
{
	float	direction;
	float	i;
	t_point	pixel;

	pixel.color = start.color;
	if (d_y > 0)
		direction = 1;
	else
		direction = -1;
	i = 0;
	while (i <= d_y * direction)
	{
		pixel.y = start.y + i * direction;
		pixel.x = start.x + i * d_x / (d_y * direction);
		(void)end;
		pixel.color = blend(start.color, end.color, i / (d_y * direction));
		put_pixel(data, (int)pixel.x, (int)pixel.y, pixel.color);
		i++;
	}
}

void	draw_line(t_point start, t_point end, t_img *img)
{
	int		d_x;
	int		d_y;

	d_x = end.x - start.x;
	d_y = end.y - start.y;
	if (d_x == 0 && d_y == 0)
		return ;
	if (fabs((double) d_x) > fabs((double) d_y))
		line_across_x(start, end, d_x, d_y, img);
	else
		line_across_y(start, end, d_x, d_y, img);
}

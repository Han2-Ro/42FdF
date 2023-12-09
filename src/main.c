/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:42:17 by hrother           #+#    #+#             */
/*   Updated: 2023/12/09 16:40:36 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars vars;
	t_data	img;
	int		win_w = 1280;
	int		win_h = 720;
	int		y;
	int		x;
	int		anim_offset;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, win_w, win_h, "Hello world!");
	mlx_hook(vars.win, 17, 1L<<0, close, &vars);
	img.img = mlx_new_image(vars.mlx, win_w, win_h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	anim_offset = 0;
	while (y < win_h)
	{
		x = 0;
		while (x < win_w)
		{
			put_pixel(&img, x, y, 255*255*x + y + anim_offset /*+ 255 * anim_offset*/);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	anim_offset++;
	mlx_loop(vars.mlx);
}

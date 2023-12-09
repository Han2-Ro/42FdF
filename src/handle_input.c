/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:46:59 by hrother           #+#    #+#             */
/*   Updated: 2023/12/09 21:07:45 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	close(int keycode, t_vars *vars)
{
	(void) keycode;
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	on_keypress(int keycode, t_vars *vars)
{
	t_data img;

	printf("Key pressed: %i\n", keycode);
	if (keycode == 119)
		vars->y -= 20;
	else if (keycode == 115)
		vars->y += 20;
	else if (keycode == 97)
		vars->x -= 20;
	else if (keycode == 100)
		vars->x += 20;
	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	t_point p1 = init_point(300, 300, 0x00FF0000);
	t_point p2 = init_point(vars->x, vars->y, 0x00FF0000);
	draw_line(p1, p2, &img);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (0);
}

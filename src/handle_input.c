/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:46:59 by hrother           #+#    #+#             */
/*   Updated: 2023/12/10 16:49:31 by hrother          ###   ########.fr       */
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
	t_data	img;

	printf("Key pressed: %i\n", keycode);
	if (keycode == 119)
		vars->pers.x_rot -= .5f;
	else if (keycode == 115)
		vars->pers.x_rot += .5f;
	else if (keycode == 97)
		vars->pers.z_rot -= .5f;
	else if (keycode == 100)
		vars->pers.z_rot += .5f;
	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_map(vars->map, &img, vars->pers);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:46:59 by hrother           #+#    #+#             */
/*   Updated: 2023/12/10 22:07:09 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	on_keypress(int keycode, t_vars *vars)
{
	t_data	img;

	printf("Key pressed: %i\n", keycode);
	if (keycode == 65362)
		vars->pers.x_rot -= .5f;
	else if (keycode == 65364)
		vars->pers.x_rot += .5f;
	else if (keycode == 65361)
		vars->pers.z_rot -= .5f;
	else if (keycode == 65363)
		vars->pers.z_rot += .5f;
	else if (keycode == 65505)
		vars->pers.zoom *= 1.1f;
	else if (keycode == 65507)
		vars->pers.zoom /= 1.1f;
	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_map(vars->map, &img, vars->pers);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (0);
}

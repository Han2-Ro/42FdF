/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:42:17 by hrother           #+#    #+#             */
/*   Updated: 2023/12/09 22:02:11 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img;
	t_map	*map;

	(void)argc;
	(void)argv;
	vars.x = 0;
	vars.y = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	//mlx_hook(vars.win, 2, 1L << 0, close, &vars);
	mlx_hook(vars.win, 17, 1L << 2, close, &vars);
	mlx_key_hook(vars.win, on_keypress, &vars);
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	map = init_map();
	draw_map(map, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}

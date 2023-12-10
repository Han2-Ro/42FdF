/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:42:17 by hrother           #+#    #+#             */
/*   Updated: 2023/12/11 00:12:30 by hannes           ###   ########.fr       */
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
	if (argc != 2)
	{
		ft_printf("usage: %s <filename>\n", argv[0]);
		return (1);
	}
	map = init_map(argv[1]);
	if (!map)
		return (1);
	print_map(*map);
	vars.pers.zoom = 1;
	vars.pers.z_rot = 0;
	vars.pers.x_rot = 0;
	vars.pers.x_trans = 0;
	vars.pers.y_trans = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	vars.map = map;
	//mlx_hook(vars.win, 2, 1L << 0, close, &vars);
	//mlx_hook(vars.win, 17, 1L << 2, close, &vars);
	mlx_key_hook(vars.win, on_keypress, &vars);
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_map(map, &img, vars.pers);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}

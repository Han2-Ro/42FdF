/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:42:17 by hrother           #+#    #+#             */
/*   Updated: 2023/12/15 14:58:23 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_vars	*init_vars(const char *filename, t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Hello world!");
	vars->map = init_map(filename);
	set_starting_pers(vars);
	vars->keys = init_keys(vars);
	return (vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_img	img;

	(void)argc;
	(void)argv;
	if (argc != 2)
	{
		ft_printf("usage: %s <filename>\n", argv[0]);
		return (1);
	}
	init_vars(argv[1], &vars);
	if (!vars.map)
		return (1);
	mlx_hook(vars.win, 17, ButtonPressMask, close_win, &vars);
	mlx_hook(vars.win, 2, KeyPressMask, on_keypressed, &vars);
	mlx_hook(vars.win, 3, KeyReleaseMask, on_keyreleased, &vars);
	mlx_loop_hook(vars.mlx, on_loop, &vars);
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	vars.img = &img;
	draw_map(vars.map, &img, vars.pers);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}

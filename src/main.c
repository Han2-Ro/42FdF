/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:42:17 by hrother           #+#    #+#             */
/*   Updated: 2024/01/06 13:49:34 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_starting_pers(t_vars *vars)
{
	int	max_map_dim;

	if (vars->map == NULL)
		return ;
	max_map_dim = vars->map->x_size;
	if (vars->map->y_size > max_map_dim)
		max_map_dim = vars->map->y_size;
	vars->pers.zoom = min(HEIGHT, WIDTH) / 1.5 / max_map_dim;
	vars->pers.y_trans = vars->map->y_size / -2;
	vars->pers.x_trans = vars->map->x_size / -2;
	vars->pers.z_trans = 0;
	vars->pers.z_rot = -1 * ROT_ANGLE;
	vars->pers.x_rot = 1 * ROT_ANGLE;
	vars->pers.z_scale = 0.5f;
	vars->pers.isoemtric = 1;
}

t_vars	*init_vars(const char *filename, t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Fil de Fer");
	vars->map = init_map(filename);
	set_starting_pers(vars);
	vars->keys = init_keys(vars);
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(
			vars->img.img,
			&vars->img.bits_per_pixel,
			&vars->img.line_length,
			&vars->img.endian);
	if (vars->map == NULL || vars->mlx == NULL || vars->win == NULL
		|| vars->img.img == NULL || vars->img.addr == NULL)
		return (NULL);
	return (vars);
}

void	setup_hooks(t_vars *vars)
{
	mlx_hook(vars->win, 17, ButtonPressMask, close_win, vars);
	mlx_hook(vars->win, 2, KeyPressMask, on_keypressed, vars);
	mlx_hook(vars->win, 3, KeyReleaseMask, on_keyreleased, vars);
	mlx_loop_hook(vars->mlx, on_loop, vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
	{
		ft_printf("usage: %s <filename>\n", argv[0]);
		return (1);
	}
	if (init_vars(argv[1], &vars) == NULL)
	{
		close_win(&vars);
		return (1);
	}
	setup_hooks(&vars);
	mlx_loop(vars.mlx);
}

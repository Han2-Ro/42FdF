/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:42:17 by hrother           #+#    #+#             */
/*   Updated: 2024/01/06 14:51:34 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_starting_pers(t_data *data)
{
	int	max_map_dim;

	if (data->map == NULL)
		return ;
	max_map_dim = data->map->x_size;
	if (data->map->y_size > max_map_dim)
		max_map_dim = data->map->y_size;
	data->pers.zoom = min(HEIGHT, WIDTH) / 1.5 / max_map_dim;
	data->pers.y_trans = data->map->y_size / -2;
	data->pers.x_trans = data->map->x_size / -2;
	data->pers.z_trans = 0;
	data->pers.z_rot = -1 * ROT_ANGLE;
	data->pers.x_rot = 1 * ROT_ANGLE;
	data->pers.z_scale = 0.5f;
	data->pers.isoemtric = 1;
}

t_data	*init_data(const char *filename, t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx)
		data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fil de Fer");
	else
		data->win = NULL;
	data->map = init_map(filename);
	set_starting_pers(data);
	data->keys = init_keys(data);
	if (data->mlx)
	{
		data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->img.addr = mlx_get_data_addr(
				data->img.img,
				&data->img.bits_per_pixel,
				&data->img.line_length,
				&data->img.endian);
	}
	else
		data->img.img = NULL;
	if (data->map == NULL || data->mlx == NULL || data->win == NULL
		|| data->img.img == NULL || data->img.addr == NULL
		|| data->keys == NULL)
		return (NULL);
	return (data);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 17, ButtonPressMask, close_win, data);
	mlx_hook(data->win, 2, KeyPressMask, on_keypressed, data);
	mlx_hook(data->win, 3, KeyReleaseMask, on_keyreleased, data);
	mlx_loop_hook(data->mlx, on_loop, data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("usage: %s <filename>\n", argv[0]);
		return (1);
	}
	if (init_data(argv[1], &data) == NULL)
	{
		close_win(&data);
		return (1);
	}
	setup_hooks(&data);
	mlx_loop(data.mlx);
}

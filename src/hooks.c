/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:56:34 by hrother           #+#    #+#             */
/*   Updated: 2024/01/06 14:51:09 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->y_size)
	{
		free(map->height[i]);
		i++;
	}
	free(map->height);
	i = 0;
	while (i < map->y_size)
	{
		free(map->color[i]);
		i++;
	}
	free(map->color);
	free(map);
}

int	close_win(t_data *data)
{
	if (data->map)
		free_map(data->map);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->keys);
	exit(0);
	return (0);
}

int	on_keypressed(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		return (close_win(data));
	else if (keycode == XK_Shift_L)
		data->pers.zoom *= 1.1f;
	else if (keycode == XK_Control_L)
		data->pers.zoom /= 1.1f;
	else if (keycode == XK_space)
		data->pers.isoemtric = !data->pers.isoemtric;
	else
		set_key(keycode, 1, data);
	return (0);
}

int	on_keyreleased(int keycode, t_data *data)
{
	return (set_key(keycode, 0, data));
}

int	on_loop(t_data *data)
{
	apply_all_keys(0.05, data);
	ft_bzero(data->img.addr, HEIGHT * data->img.line_length);
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:46:59 by hrother           #+#    #+#             */
/*   Updated: 2023/12/12 15:55:31 by hrother          ###   ########.fr       */
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
	free(map);
}

int	close_win(int keycode, t_vars *vars)
{
	(void) keycode;
	free_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
	return (0);
}

int	on_keypress(int keycode, t_vars *vars)
{
	printf("Key pressed: %i\n", keycode);
	if (keycode == 65307)
		return (close_win(keycode, vars));
	else if (keycode == 65362)
		vars->pers.x_rot += .5f;
	else if (keycode == 65364)
		vars->pers.x_rot -= .5f;
	else if (keycode == 65361)
		vars->pers.z_rot += .5f;
	else if (keycode == 65363)
		vars->pers.z_rot -= .5f;
	else if (keycode == 65505)
		vars->pers.zoom *= 1.1f;
	else if (keycode == 65507)
		vars->pers.zoom /= 1.1f;
	else if (keycode == 119)
		vars->pers.y_trans -= 1;
	else if (keycode == 115)
		vars->pers.y_trans += 1;
	else if (keycode == 97)
		vars->pers.x_trans -= 1;
	else if (keycode == 100)
		vars->pers.x_trans += 1;
	ft_bzero(vars->img->addr, HEIGHT * vars->img->line_length);
	draw_map(vars->map, vars->img, vars->pers);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

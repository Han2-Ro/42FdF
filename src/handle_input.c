/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:46:59 by hrother           #+#    #+#             */
/*   Updated: 2023/12/14 20:03:40 by hrother          ###   ########.fr       */
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

int	close_win(t_vars *vars)
{
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
	if (keycode == XK_Escape)
		return (close_win(vars));
	else if (keycode == XK_Up)
		vars->pers.x_rot += ROT_ANGLE;
	else if (keycode == XK_Down)
		vars->pers.x_rot -= ROT_ANGLE;
	else if (keycode == XK_Left)
		vars->pers.z_rot += ROT_ANGLE;
	else if (keycode == XK_Right)
		vars->pers.z_rot -= ROT_ANGLE;
	else if (keycode == XK_Shift_L)
		vars->pers.zoom *= 1.1f;
	else if (keycode == XK_Control_L)
		vars->pers.zoom /= 1.1f;
	else if (keycode == XK_q)
		vars->pers.y_trans -= 1;
	else if (keycode == XK_e)
		vars->pers.y_trans += 1;
	else if (keycode == XK_a)
		vars->pers.x_trans -= 1;
	else if (keycode == XK_d)
		vars->pers.x_trans += 1;
	else if (keycode == XK_w)
		vars->pers.z_trans += 1;
	else if (keycode == XK_s)
		vars->pers.z_trans -= 1;
	else if (keycode == XK_space)
		vars->pers.isoemtric = !vars->pers.isoemtric;
	ft_bzero(vars->img->addr, HEIGHT * vars->img->line_length);
	draw_map(vars->map, vars->img, vars->pers);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

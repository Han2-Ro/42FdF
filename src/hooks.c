/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:56:34 by hrother           #+#    #+#             */
/*   Updated: 2023/12/14 21:26:08 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	on_keypressed(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		return (close_win(vars));
	else if (keycode == XK_Shift_L)
		vars->pers.zoom *= 1.1f;
	else if (keycode == XK_Control_L)
		vars->pers.zoom /= 1.1f;
	else if (keycode == XK_space)
		vars->pers.isoemtric = !vars->pers.isoemtric;
	else
		set_key(keycode, 1, vars);
	return (0);
}

int	on_keyreleased(int keycode, t_vars *vars)
{
	return (set_key(keycode, 0, vars));
}

int	on_loop(t_vars *vars)
{
	apply_all_keys(0.05, vars);
	ft_bzero(vars->img->addr, HEIGHT * vars->img->line_length);
	draw_map(vars->map, vars->img, vars->pers);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

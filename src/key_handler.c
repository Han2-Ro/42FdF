/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:28:39 by hrother           #+#    #+#             */
/*   Updated: 2024/01/05 14:56:28 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_key	init_key(int keycode, float dif, float *val)
{
	t_key	key;

	key.keycode = keycode;
	key.dif = dif;
	key.val = val;
	key.pressed = 0;
	return (key);
}

t_key	*init_keys(t_vars *vars)
{
	t_key	*keys;
	float	dif_trans;

	dif_trans = vars->map->x_size / 10;
	keys = malloc(20 * sizeof(t_key));
	if (!keys)
		return (NULL);
	keys[0] = init_key(XK_Up, ROT_ANGLE, &vars->pers.x_rot);
	keys[1] = init_key(XK_Down, -ROT_ANGLE, &vars->pers.x_rot);
	keys[2] = init_key(XK_Left, ROT_ANGLE, &vars->pers.z_rot);
	keys[3] = init_key(XK_Right, -ROT_ANGLE, &vars->pers.z_rot);
	keys[4] = init_key(XK_q, -dif_trans, &vars->pers.y_trans);
	keys[5] = init_key(XK_e, dif_trans, &vars->pers.y_trans);
	keys[6] = init_key(XK_a, -dif_trans, &vars->pers.x_trans);
	keys[7] = init_key(XK_d, dif_trans, &vars->pers.x_trans);
	keys[8] = init_key(XK_w, dif_trans, &vars->pers.z_trans);
	keys[9] = init_key(XK_s, -dif_trans, &vars->pers.z_trans);
	keys[10] = init_key(0, 0, 0);
	return (keys);
}

int	set_key(int keycode, int state, t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->keys[i].keycode != 0)
	{
		if (vars->keys[i].keycode == keycode)
		{
			vars->keys[i].pressed = state;
			return (0);
		}
		i++;
	}
	return (1);
}

void	apply_all_keys(float deltatime, t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->keys[i].keycode != 0)
	{
		if (vars->keys[i].pressed)
			*vars->keys[i].val += vars->keys[i].dif * deltatime;
		i++;
	}
}

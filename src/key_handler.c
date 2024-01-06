/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:28:39 by hrother           #+#    #+#             */
/*   Updated: 2024/01/06 14:51:23 by hannes           ###   ########.fr       */
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

t_key	*init_keys(t_data *data)
{
	t_key	*keys;
	float	dif_trans;

	if (data->map == NULL)
		return (NULL);
	dif_trans = data->map->x_size / 10;
	keys = malloc(20 * sizeof(t_key));
	if (!keys)
		return (NULL);
	keys[0] = init_key(XK_Up, ROT_ANGLE, &data->pers.x_rot);
	keys[1] = init_key(XK_Down, -ROT_ANGLE, &data->pers.x_rot);
	keys[2] = init_key(XK_Left, ROT_ANGLE, &data->pers.z_rot);
	keys[3] = init_key(XK_Right, -ROT_ANGLE, &data->pers.z_rot);
	keys[4] = init_key(XK_q, -dif_trans, &data->pers.y_trans);
	keys[5] = init_key(XK_e, dif_trans, &data->pers.y_trans);
	keys[6] = init_key(XK_a, -dif_trans, &data->pers.x_trans);
	keys[7] = init_key(XK_d, dif_trans, &data->pers.x_trans);
	keys[8] = init_key(XK_w, dif_trans, &data->pers.z_trans);
	keys[9] = init_key(XK_s, -dif_trans, &data->pers.z_trans);
	keys[10] = init_key(0, 0, 0);
	return (keys);
}

int	set_key(int keycode, int state, t_data *data)
{
	int	i;

	i = 0;
	while (data->keys[i].keycode != 0)
	{
		if (data->keys[i].keycode == keycode)
		{
			data->keys[i].pressed = state;
			return (0);
		}
		i++;
	}
	return (1);
}

void	apply_all_keys(float deltatime, t_data *data)
{
	int	i;

	i = 0;
	while (data->keys[i].keycode != 0)
	{
		if (data->keys[i].pressed)
			*data->keys[i].val += data->keys[i].dif * deltatime;
		i++;
	}
}

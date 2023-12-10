/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:18:06 by hrother           #+#    #+#             */
/*   Updated: 2023/12/10 17:19:15 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_map	*init_map(void)
{
	t_map	*map;
	int		i;
	int		j;

	map = malloc(sizeof(t_map));
	map->x_size = 4;
	map->y_size = 4;
	map->arr = malloc(map->x_size * sizeof(float *));
	i = 0;
	while (i < map->x_size)
	{
		map->arr[i] = malloc(map->y_size * sizeof(float));
		j = 0;
		while (j < map->y_size)
		{
			map->arr[i][j] = .0f;
			j++;
		}
		i++;
	}
	map->arr[1][1] = 0.5f;
	map->arr[1][2] = 0.5f;
	map->arr[2][1] = 0.5f;
	map->arr[2][2] = 0.5f;
	return (map);
}

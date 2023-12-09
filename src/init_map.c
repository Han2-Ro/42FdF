/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:18:06 by hrother           #+#    #+#             */
/*   Updated: 2023/12/09 21:28:42 by hrother          ###   ########.fr       */
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
	map->arr = malloc(map->x_size * sizeof(int *));
	i = 0;
	while (i < map->x_size)
	{
		map->arr[i] = malloc(map->y_size * sizeof(int));
		j = 0;
		while (j < map->y_size)
		{
			map->arr[i][j] = 0;
			j++;
		}
		i++;
	}
	return (map);
}

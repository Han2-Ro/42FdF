/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:18:06 by hrother           #+#    #+#             */
/*   Updated: 2023/12/12 18:50:01 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	*str_attach(char **s1, char *s2)
{
	char	*res;

	res = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = res;
	return (res);
}

char	*read_file(char *filename)
{
	char	*str;
	char	buffer[16];
	int		bytes_read;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		ft_bzero(buffer, 16);
		bytes_read = read(fd, buffer, 15);
		str_attach(&str, buffer);
	}
	return (str);
}

int	fill_row(char	*line, int size, t_map *map, int y)
{
	char	**cells;
	int		x;
	char	*color;

	cells = ft_split(line, ' ');
	map->height[y] = malloc(size * sizeof(int));
	map->color[y] = malloc(size * sizeof(int));
	if (!map->height[y] || !map->color[y] || !cells)
		return (0);
	x = 0;
	while (cells[x] && x < size)
	{
		map->height[y][x] = ft_atoi(cells[x]);
		color = ft_strnstr(cells[x], ",0x", 30);
		if (color)
			map->color[y][x] = ft_atoi_base(color + 3, HEX);
		else
			map->color[y][x] = 0x00FFFFFF;
		x++;
	}
	free_strs(cells);
	return (1);
}

t_map	*parse_map(t_map *map, char	*str)
{
	int		y;
	char	**lines;

	map->y_size = count_w(str, '\n');
	lines = ft_split(str, '\n');
	map->height = malloc(map->y_size * sizeof (int *));
	map->color = malloc(map->y_size * sizeof (int *));
	if (!lines || !map->height)
		return (NULL);
	map->x_size = count_w(lines[0], ' ');
	y = 0;
	while (lines[y] && y < map->y_size)
	{
		fill_row(lines[y], map->x_size, map, y);
		y++;
	}
	free_strs(lines);
	return (map);
}

t_map	*init_map(char *filename)
{
	t_map	*map;
	char	*str;

	str = read_file(filename);
	//printf("%s\n\n", str);
	if (!str)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (map)
		parse_map(map, str);
	free(str);
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:18:06 by hrother           #+#    #+#             */
/*   Updated: 2024/01/06 19:27:33 by hrother          ###   ########.fr       */
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

char	*read_file(const char *filename)
{
	char	*str;
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Could not open file", 2), NULL);
	str = malloc(sizeof(char));
	if (!str)
		return (close(fd), NULL);
	str[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
		str_attach(&str, buffer);
	}
	close(fd);
	return (str);
}

int	fill_row(char	*line, int size, t_map *map, int y)
{
	char	**cells;
	int		x;
	char	*color;

	cells = ft_split(line, ' ');
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
	while (x < size)
	{
		map->height[y][x] = 0;
		map->color[y][x] = 0x00FFFFFF;
		x++;
	}
	return (free_strs(cells), 1);
}

t_map	*parse_map(t_map *map, char	*str)
{
	int		y;
	char	**lines;

	map->y_size = count_w(str, '\n');
	lines = ft_split(str, '\n');
	map->height = calloc(map->y_size, sizeof (int *));
	map->color = calloc(map->y_size, sizeof (int *));
	if (!lines || !map->height || !map->color)
		return (free_strs(lines), free(map->height),
			free(map->color), free(map), NULL);
	map->x_size = count_w(lines[0], ' ');
	y = 0;
	while (lines[y] && y < map->y_size)
	{
		map->height[y] = malloc(map->x_size * sizeof(int));
		map->color[y] = malloc(map->x_size * sizeof(int));
		if (!map->height[y] || !map->color[y])
			return (free_map(map), free_strs(lines), NULL);
		if (!fill_row(lines[y], map->x_size, map, y))
			return (free_map(map), free_strs(lines), NULL);
		y++;
	}
	free_strs(lines);
	return (map);
}

t_map	*init_map(const char *filename)
{
	t_map	*map;
	char	*str;
	int		len;

	len = ft_strlen(filename);
	if (len <= 4 || filename[len - 4] != '.'
		|| filename[len - 3] != 'f'
		|| filename[len - 2] != 'd'
		|| filename[len - 1] != 'f')
		return (ft_putendl_fd("File extension must be .fdf", 2), NULL);
	str = read_file(filename);
	if (!str)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (map)
		map = parse_map(map, str);
	free(str);
	return (map);
}

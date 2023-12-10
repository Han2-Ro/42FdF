/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:18:06 by hrother           #+#    #+#             */
/*   Updated: 2023/12/10 20:05:20 by hrother          ###   ########.fr       */
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
	ft_bzero(buffer, 16);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 15);
		str_attach(&str, buffer);
	}
	return (str);
}

float	*parse_row(char	*line, int size)
{
	char	**cells;
	int		x;
	float	*row;

	cells = ft_split(line, ' ');
	row = malloc(size * sizeof(int));
	if (!row || !cells)
		return (NULL);
	x = 0;
	while (cells[x] && x < size)
	{
		row[x] = ft_atoi(cells[x]);
		x++;
	}
	free_strs(cells);
	return (row);
}

t_map	*parse_map(t_map *map, char	*str)
{
	int		y;
	char	**lines;

	lines = ft_split(str, '\n');
	map->arr = malloc(map->y_size * sizeof (int *));
	if (!lines || !map->arr)
		return (NULL);
	y = 0;
	while (lines[y] && y < map->y_size)
	{
		map->arr[y] = parse_row(lines[y], map->x_size);
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
	printf("%s\n\n", str);
	map = malloc(sizeof(t_map));
	map->x_size = 4;
	map->y_size = 4;
	parse_map(map, str);
	free(str);
	return (map);
}

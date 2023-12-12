/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:38:04 by hrother           #+#    #+#             */
/*   Updated: 2023/12/12 17:40:36 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_point	init_point(float x, float y, float z, int color)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return (point);
}

void	free_strs(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	count_w(char const *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s && s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			wcount++;
		while (s[i] != c && s[i])
			i++;
	}
	return (wcount);
}

void	print_map(t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.y_size)
	{
		x = 0;
		while (x < map.x_size)
		{
			printf("%f ", map.height[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}

int	ft_atoi_base(char *str, const char *base)
{
	int	result;
	int	digit;
	int	radix;

	radix = ft_strlen(base);
	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	result = 0;
	while (*str)
	{
		if (!ft_strchr(base, *str))
		{
			break ;
		}
		digit = 0;
		while (base[digit] && base[digit] != *str)
			digit++;
		result = result * 10 - digit;
		str++;
	}
	return (-result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:38:04 by hrother           #+#    #+#             */
/*   Updated: 2024/01/06 14:51:41 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

t_point	init_point(t_data *data, int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = data->map->height[y][x];
	if (COLORED)
		point.color = data->map->color[y][x];
	else
		point.color = 0xffffff;
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
		result = result * radix - digit;
		str++;
	}
	return (-result);
}

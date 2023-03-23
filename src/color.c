/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:29:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 15:42:35 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_gradient(int start, int end, double len, double pos)
{
	t_color	one;
	t_color	two;
	t_color	ret;
	double	t;

	t = pos / len;
	one.a = (start >> 24 & 0xFF);
	one.r = (start >> 16 & 0xFF);
	one.g = (start >> 8 & 0xFF);
	one.b = (start & 0xFF);
	two.a = (end >> 24 & 0xFF);
	two.r = (end >> 16 & 0xFF);
	two.g = (end >> 8 & 0xFF);
	two.b = (end & 0xFF);
	ret.a = one.a + t * (two.a - one.a);
	ret.r = one.r + t * (two.r - one.r);
	ret.g = one.g + t * (two.g - one.g);
	ret.b = one.b + t * (two.b - one.b);
	return ((ret.a << 24) | (ret.r << 16) | (ret.g << 8) | ret.b);
}

void	ft_set_pattern(int pattern[4], int choice)
{
	static const int	colorschemes[5][5] = {
	{YELLOW, RED, BLUE, BLACK, STANDARD},
	{BLACK, BLACK, BLACK, WHITE, B_AND_W},
	{TYRES, MICHELIN, BLACK, TOKYODRIFT, RUPPI},
	{BLACK, GREEN, BLACK, BLACK, MATRIX},
	{PURPLE, ORANGE, PINK, LIGHTBLUE, POP}
	};

	pattern[0] = colorschemes[choice][0];
	pattern[1] = colorschemes[choice][1];
	pattern[2] = colorschemes[choice][2];
	pattern[3] = colorschemes[choice][3];
	pattern[4] = colorschemes[choice][4];
}

void	ft_set_morph_color(t_vec3f *points, t_vec3f *morph, t_map *map)
{
	int	i;
	int	*pattern;

	pattern = map->pattern;
	i = 0;
	while (i < map->sum_points)
	{
		if (map->hex)
		{
			if (!points[i].color)
				morph[i].color = pattern[1];
			else
				morph[i].color = points[i].color;
		}
		else if (points[i].z == 0)
			morph[i].color = pattern[1];
		else if (points[i].z > 0)
			morph[i].color = ft_gradient(pattern[1], pattern[2], \
					map->limits[ZMAX], points[i].z);
		else
			morph[i].color = ft_gradient(pattern[1], pattern[0], \
					map->limits[ZMIN], points[i].z);
		i++;
	}
}

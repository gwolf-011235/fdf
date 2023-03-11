/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:29:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/11 11:23:35 by gwolf            ###   ########.fr       */
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
	static const int	colorschemes[5][4] = {
	{YELLOW, RED, BLUE, BLACK},
	{BLACK, BLACK, BLACK, WHITE},
	{TYRES, MICHELIN, BLACK, TOKYODRIFT},
	{BLACK, GREEN, BLACK, BLACK},
	{PURPLE, ORANGE, PINK, LIGHTBLUE}
	};

	pattern[0] = colorschemes[choice][0];
	pattern[1] = colorschemes[choice][1];
	pattern[2] = colorschemes[choice][2];
	pattern[3] = colorschemes[choice][3];
}

void	ft_set_morph_color(t_vec3f *morph, t_vec3f *points, int sum)
{
	int	i;

	i = 0;
	while (i < sum)
	{
		morph[i].color = points[i].color;
		i++;
	}
}

void	ft_set_argb_values(t_color *color, uint8_t r, uint8_t g, uint8_t b)
{
	color->a = 0;
	color->r = r;
	color->g = g;
	color->b = b;
}

uint32_t	ft_raindbow(double ratio)
{
	int		normalized;
	int		region;
	int		x;
	t_color	ret;

	normalized = (int)(ratio * 256 * 6);
	region = normalized / 256;
	x = normalized % 256;

	if (region == 0)
		ft_set_argb_values(&ret, 255, 0 + x, 0);
	else if (region == 1)
		ft_set_argb_values(&ret, 255 - x, 255, 0);
	else if (region == 2)
		ft_set_argb_values(&ret, 0, 255, 0 + x);
	else if (region == 3)
		ft_set_argb_values(&ret, 0, 255 - x, 255);
	else if (region == 4)
		ft_set_argb_values(&ret, 0 + x, 0, 255);
	else if (region == 5)
		ft_set_argb_values(&ret, 255, 0, 255 - x);
	return ((ret.a << 24) | (ret.r << 16) | (ret.g << 8) | ret.b);
}

void	ft_skittles(t_map *map, t_vec3f *morph)
{
	int	i;
	float	ratio;
	static float offset;

	i = 0;
	offset += 0.01 * map->factor;
	while (i < map->sum_points)
	{
		ratio = morph[i].y / map->props.canvas[Y] + offset;
		ratio = fmod(ratio, 1.0);
		morph[i].color = ft_raindbow(ratio);
		i++;
	}
}

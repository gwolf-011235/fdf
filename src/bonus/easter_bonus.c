/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wobble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:44:20 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/22 10:13:05 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_wobble(t_vec3f *morph, t_vec3f *points, t_mat4 mat, t_map *map)
{
	int		i;
	int		neg;

	i = 0;
	while (i < map->sum_points)
	{
		neg = 1;
		morph[i].x = points[i].x * mat[0][0] + points[i].y * mat[1][0]
			+ points[i].z * mat[2][0] + mat[3][0]
			+ (rand() % (map->factor * 2)) * neg;
		morph[i].y = points[i].x * mat[0][1] + points[i].y * mat[1][1]
			+ points[i].z * mat[2][1] + mat[3][1]
			+(rand() % (map->factor * 2)) * neg;
		morph[i].z = points[i].x * mat[0][2] + points[i].y * mat[1][2]
			+ points[i].z * mat[2][2] + mat[3][2]
			+ (rand() % (map->factor * 2)) * neg;
		if (morph[i].x < 0 || morph[i].x > map->props.canvas[X]
			|| morph[i].y < 0 || morph[i].y > map->props.canvas[Y])
			morph[i].hidden = true;
		else
			morph[i].hidden = false;
		i++;
	}
}

uint32_t	ft_rainbow(double ratio)
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
	int				i;
	float			ratio;
	static float	offset;

	i = 0;
	offset += 0.01 * map->factor;
	while (i < map->sum_points)
	{
		ratio = morph[i].y / map->props.canvas[Y] + offset;
		ratio = fmod(ratio, 1.0);
		morph[i].color = ft_rainbow(ratio);
		i++;
	}
}

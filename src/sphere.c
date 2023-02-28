/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:34:37 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/28 19:54:20 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_convert_spherical(t_map *map, int sum)
{
	int		i;
	float	step_longi;
	float	step_lati;

	i = 0;
	step_longi = (M_PI * 2) / map->max[X];
	step_lati = M_PI / map->max[Y];
	map->radius = map->width / (2 * M_PI);
	while (i < sum)
	{
		map->points[i + i].angle[LON] = -(map->points[i + i].x) * step_longi;
		map->points[i + i].angle[LAT] = map->points[i + i].y * step_lati;
		if (map->points[i + i].y > 0)
			map->points[i + i].angle[LAT] = (map->points[i + i].y + (map->max[Y] / 2)) * step_lati - 0.5 * step_lati;
		else
			map->points[i + i].angle[LAT] = (map->points[i + i].y + (map->max[Y] / 2) - 1) * step_lati + 0.5 * step_lati;
		i++;
	}
}

void	ft_convert_sphere2cart(t_map *map, t_vec3f *polar)
{
	int	i;

	i = 0;
	float factor = (M_PI * 2) / map->max[Z];
	while (i < map->sum_points)
	{
		polar[i + i].x = (map->radius + factor * map->points[i + i].z) * sin(map->points[i + i].angle[LAT]) * cos(map->points[i + i].angle[LON]);
		polar[i + i].y = (map->radius + factor * map->points[i + i].z) * sin(map->points[i + i].angle[LAT]) * sin(map->points[i + i].angle[LON]);
		polar[i + i].z = (map->radius + factor * map->points[i + i].z) * cos(map->points[i + i].angle[LAT]);
		polar[i + i].color = map->points[i + i].color;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:34:37 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/05 21:50:15 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_ang_coords(t_map *map, int sum)
{
	int		i;
	float	step_lon;
	float	step_lat;

	i = 0;
	step_lon = (2 * M_PI) / map->max[X];
	step_lat = M_PI / map->max[Y];
	map->radius = map->width / (2 * M_PI);
	while (i < sum)
	{
		map->ang_coord[i].lon = map->points[i].x * step_lon;
		map->ang_coord[i].lat = map->points[i].y * step_lat;
		i++;
	}
}

void	ft_calc_sphere_points(t_map *map, t_coord *ang_coord, t_vec3f *polar)
{
	int		i;
	float	z_offset;

	i = 0;
	while (i < map->sum_points)
	{
		z_offset = map->z_storage[i] * map->props.scale_z;
		polar[i].x = (map->radius + z_offset) * sin(ang_coord[i].lat)
			* cos(ang_coord[i].lon);
		polar[i].y = (map->radius + z_offset) * sin(ang_coord[i].lat)
			* sin(ang_coord[i].lon);
		polar[i].z = (map->radius + z_offset) * cos(ang_coord[i].lat);
		polar[i].color = map->points[i].color;
		i++;
	}
}

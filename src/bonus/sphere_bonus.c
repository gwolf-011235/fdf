/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:34:37 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 15:02:58 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_set_lonlat(t_map *map, int sum)
{
	int		i;
	float	step_lon;
	float	step_lat;

	i = 0;
	step_lon = (2 * M_PI) / map->limits[XMAX];
	step_lat = M_PI / map->limits[YMAX];
	map->radius = map->width / (2 * M_PI);
	while (i < sum)
	{
		map->lonlat[i].lon = map->points[i].x * step_lon;
		map->lonlat[i].lat = map->points[i].y * step_lat;
		i++;
	}
}

void	ft_find_limits_sphere(t_map *map, t_vec3f *sphere)
{
	int	i;

	ft_memset(map->limits_sp, 0, sizeof(map->limits_sp));
	i = 0;
	while (i < map->sum_points)
	{
		map->limits_sp[XMAX] = fmax(sphere[i].x, map->limits_sp[XMAX]);
		map->limits_sp[XMIN] = fmin(sphere[i].x, map->limits_sp[XMIN]);
		map->limits_sp[YMAX] = fmax(sphere[i].y, map->limits_sp[YMAX]);
		map->limits_sp[YMIN] = fmin(sphere[i].y, map->limits_sp[YMIN]);
		map->limits_sp[ZMAX] = fmax(sphere[i].z, map->limits_sp[ZMAX]);
		map->limits_sp[ZMIN] = fmin(sphere[i].z, map->limits_sp[ZMIN]);
		i++;
	}
}

void	ft_calc_sphere_points(t_map *map, t_lonlat *lonlat, t_vec3f *sphere)
{
	int		i;
	float	z_offset;

	i = 0;
	while (i < map->sum_points)
	{
		z_offset = map->z_storage[i] * map->props.scale_z;
		sphere[i].x = (map->radius + z_offset) * sin(lonlat[i].lat)
			* cos(lonlat[i].lon);
		sphere[i].y = (map->radius + z_offset) * sin(lonlat[i].lat)
			* sin(lonlat[i].lon);
		sphere[i].z = (map->radius + z_offset) * cos(lonlat[i].lat);
		sphere[i].color = map->points[i].color;
		i++;
	}
	ft_find_limits_sphere(map, sphere);
	ft_set_corners(map->corner[2], map->limits_sp);
}

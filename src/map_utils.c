/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:27:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/10 11:48:29 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map_init(t_map *map)
{
	ft_set_pattern(map->pattern, 0);
	map->props.angle[X] = atan(sqrt(2)) * 180 / M_PI;
	map->props.angle[Y] = 0;
	map->props.angle[Z] = 45;
	map->props.translate[Z] = 1;
	map->factor = 1;
	map->skip = 1;
}

void	ft_find_limits_z(t_map *map)
{
	int	i;

	map->limits[ZMAX] = 0;
	map->limits[ZMIN] = 0;
	i = 0;
	while (i < map->sum_points)
	{
		map->limits[ZMAX] = fmax(map->points[i].z, map->limits[ZMAX]);
		map->limits[ZMIN] = fmin(map->points[i].z, map->limits[ZMIN]);
		i++;
	}
}

void	ft_set_limits_xy(t_map *map)
{
	map->limits[XMIN] = -(map->width / 2);
	map->limits[YMIN] = -(map->height / 2);
	map->limits[XMAX] = map->limits[XMIN] * -1;
	map->limits[YMAX] = map->limits[YMIN] * -1;
	if (!(map->width % 2))
		map->limits[XMAX]--;
	if (!(map->height % 2))
		map->limits[YMAX]--;
}

void	ft_fill_z_storage(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->sum_points)
	{
		map->z_storage[i] = map->points[i].z;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		map->z_storage[map->sum_points + i] = map->limits[ZMIN];
		map->z_storage[map->sum_points + 4 + i] = map->limits[ZMAX];
		i++;
	}
}

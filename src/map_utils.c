/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:27:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/08 17:33:13 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map_init(t_map *map)
{
	ft_set_pattern(map->pattern, 0, 5);
	map->props.angle[X] = atan(sqrt(2)) * 180 / M_PI;
	map->props.angle[Y] = 0;
	map->props.angle[Z] = 45;
	map->props.translate[Z] = 1;
	map->factor = 1;
}

void	ft_find_limits_z(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->sum_points)
	{
		map->max[Z] = fmax(map->points[i].z, map->max[Z]);
		map->min[Z] = fmin(map->points[i].z, map->min[Z]);
		i++;
	}
}

void	ft_set_limits_xy(t_map *map)
{
	map->min[X] = -(map->width / 2);
	map->min[Y] = -(map->height / 2);
	map->max[X] = map->min[X] * -1;
	map->max[Y] = map->min[Y] * -1;
	if (!(map->width % 2))
		map->max[X]--;
	if (!(map->height % 2))
		map->max[Y]--;
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
		map->z_storage[map->sum_points + i] = map->min[Z];
		map->z_storage[map->sum_points + 4 + i] = map->max[Z];
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:27:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 12:01:50 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

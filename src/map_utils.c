/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:27:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/16 21:24:22 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map_init(t_map *map)
{
	map->scale = 10;
	map->roll = 0;
	map->pitch = 0;
	map->yaw = 0;
	map->trans_x = 0;
	map->trans_y = 0;
	map->pattern[0] = BLUE;
	map->pattern[1] = GREEN;
	map->pattern[2] = RED;
}

void	ft_find_extremes(t_map *map, int z)
{
	if (z > map->max[Z])
	{
		map->max[Z] = z;
	}
	if (z < map->min[Z])
	{
		map->min[Z] = z;
	}
}

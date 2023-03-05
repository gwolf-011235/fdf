/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:27:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/05 07:43:55 by gwolf            ###   ########.fr       */
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

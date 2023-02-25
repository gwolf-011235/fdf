/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:27:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/25 20:01:21 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map_init(t_map *map)
{
	ft_set_pattern(map->pattern, 0);
	map->props.angle[X] = 0;
	map->props.angle[Z] = 0;
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

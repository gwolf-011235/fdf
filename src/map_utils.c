/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:27:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/18 22:29:42 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map_init(t_map *map)
{
	map->pattern[0] = BLUE;
	map->pattern[1] = GREEN;
	map->pattern[2] = RED;
	map->props.angle[X] = 45;
	map->props.angle[Z] = 27;
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

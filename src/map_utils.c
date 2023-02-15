/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:27:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/15 13:50:40 by gwolf            ###   ########.fr       */
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
	map->top = 0;
	map->low = 0;
	map->color_top = RED;
	map->color_mid = GREEN;
	map->color_low = BLUE;
}

void	ft_find_extremes(t_map *map, int z)
{
	if (z > map->top)
	{
		map->top = z;
	}
	if (z < map->low)
	{
		map->low = z;
	}
}

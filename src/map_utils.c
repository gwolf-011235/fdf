/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:27:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/05 22:12:59 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map_init(t_map *map)
{
	map->ang_x = 0;
	map->ang_y = 0;
	map->ang_z = 0;
	map->scale = 10;
	map->offset_x = (WIN_X / 2);
	map->offset_y = (WIN_Y / 2);
	map->trans_x = 0;
	map->trans_y = 0;
	map->top = 0;
	map->low = 0;
	map->color_top = COLOR_TOP;
	map->color_mid = COLOR_MID;
	map->color_low = COLOR_LOW;
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

void	ft_copy_map(t_map *map)
{
	ft_memcpy(map->morph, map->points, (map->sum_points * sizeof(t_point)));
}

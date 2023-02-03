/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/03 10:39:01 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_shape_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->sum_points)
	{
		map->morph[i].color = gradient(COLOR_TOP, COLOR_MID, map->top, map->morph[i].z);
		rotate(&map->points[i], map->ang_x, map->ang_y, map->ang_z);
		map->morph[i].x = map->morph[i].x * map->scale;
		map->morph[i].y = map->morph[i].y * map->scale;
		map->morph[i].z = map->morph[i].z * map->scale;
		i++;
	}
	i = 0;
	while (i < map->sum_points)
	{
		map->morph[i] = project_2d(map->morph[i]);
		map->morph[i].x = map->morph[i].x + map->offset_x;
		map->morph[i].y = map->morph[i].y + map->offset_y;
		i++;
	}
}

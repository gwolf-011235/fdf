/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/05 22:13:56 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_shape_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->sum_points)
	{
		rotate(&map->morph[i], map->ang_x, map->ang_y, map->ang_z);
		map->morph[i].x = map->morph[i].x * map->scale;
		map->morph[i].y = map->morph[i].y * map->scale;
		map->morph[i].z = map->morph[i].z * map->scale;
		map->morph[i].x = map->morph[i].x + map->trans_x;
		map->morph[i].y = map->morph[i].y + map->trans_y;
		map->morph[i].x = map->morph[i].x + WIN_X * 0.5;
		map->morph[i].y = map->morph[i].y + WIN_Y * 0.5;
		//project_2d(&map->morph[i]);
		i++;
	}
}

void	ft_redraw(t_data *data)
{
	ft_copy_map(&data->map);
	ft_shape_map(&data->map);
	fill_background(&data->img);
	lines(&data->img, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

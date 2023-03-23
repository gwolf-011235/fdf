/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:27:53 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/22 11:15:59 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		map->z_storage[map->sum_points + i] = map->limits[ZMIN];
		map->z_storage[map->sum_points + 4 + i] = map->limits[ZMAX];
		i++;
	}
}

void	ft_set_canvas_size(int canvas[4], int x, int y)
{
	if (x)
	{
		if (canvas[X] == 0)
			canvas[X] = x;
		else
			canvas[X] += x;
		canvas[OFFSET_X] = canvas[X] / 2;
	}
	if (y)
	{
		if (canvas[Y] == 0)
			canvas[Y] = y;
		else
			canvas[Y] += y;
		canvas[OFFSET_Y] = canvas[Y] / 2;
	}
}

void	ft_set_ft_ptr(t_data *data, int choose)
{
	static const t_calc_ft	calc_ptr[2] = {ft_calc_morph, ft_wobble};
	static const t_draw_ft	draw_ptr[2] = {ft_draw_wirelines, ft_draw_points};

	if (choose == 0)
		data->calc_ft = calc_ptr[0];
	else if (choose == 1)
		data->calc_ft = calc_ptr[1];
	else if (choose == 2)
		data->draw_ft = draw_ptr[0];
	else if (choose == 3)
		data->draw_ft = draw_ptr[1];
}

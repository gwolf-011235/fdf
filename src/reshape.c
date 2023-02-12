/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/12 10:30:13 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_shape_map(t_map *map) //init trans or smth
{
	int		i;

	ft_init_mat4(map->trans);
	map->trans[0][0] = map->scale;
	map->trans[1][1] = map->scale;
	map->trans[2][2] = map->scale;
	map->trans[3][3] = 1;
	ft_rotate_x(map->trans, map->roll);
	ft_rotate_y(map->trans, map->pitch);
	ft_rotate_z(map->trans, map->yaw);
	map->trans[3][0] = map->trans_x + map->offset_x;
	map->trans[3][1] = map->trans_y + map->offset_y;

	i = 0;
	while (i < map->sum_points)
	{
		map->points[i D M] = ft_mult_vec3f_mat4(map->points[i D], map->trans);
		i++;
	}
}

void	ft_redraw(t_data *data)
{
	ft_shape_map(&data->map);
	fill_background(&data->render);
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
}

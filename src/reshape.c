/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/10 16:17:04 by gwolf            ###   ########.fr       */
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
	map->trans[0][3] = map->trans_x + map->offset_x;
	map->trans[1][3] = map->trans_y + map->offset_y;
	i = 0;
	while (i < map->sum_points)
	{
		map->morph[i] = ft_mult_vec3f_mat4(map->morph[i], map->trans);
		i++;
	}
}

void	ft_redraw(t_data *data)
{
	ft_copy_map(&data->map);
	ft_shape_map(&data->map);
	fill_background(&data->render);
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
}

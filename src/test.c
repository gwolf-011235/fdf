/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:15:46 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/10 13:33:24 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	test(t_data *data)
{
	t_mat4 trans;
	t_map *map;

	map = &data->map;


	int	i;

	i = 0;
	while (i < data->map.sum_points)
	{
		map->morph[i] = ft_mult_vec3f_mat4(map->morph[i], trans);
		//map->morph[i].x = map->morph[i].x * map->scale;
		//map->morph[i].y = map->morph[i].y * map->scale;
		//map->morph[i].z = map->morph[i].z * map->scale;
		//map->morph[i].x = map->morph[i].x + map->offset_x;
		//map->morph[i].y = map->morph[i].y + map->offset_y;
		i++;
	}
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
	mlx_hook(data->win, 2, 1L<<0, close_window, data);
	mlx_loop(data->mlx);
}

	/*
	ft_init_window(data);
	ft_init_menu(data);
	mlx_hook(data->win, 2, 1L<<0, close_window, data);
	mlx_string_put(data->mlx, data->win, 160, 50, 0x0, data->map.filename);
	mlx_string_put(data->mlx, data->win, 160, 120, 0x0, "0");
	mlx_string_put(data->mlx, data->win, 160, 140, 0x0, "10");
	mlx_string_put(data->mlx, data->win, 160, 160, 0x0, "This is long string");
	mlx_loop(data->mlx);
	*/

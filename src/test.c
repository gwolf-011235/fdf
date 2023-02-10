/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:15:46 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/10 16:31:28 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	test(t_data *data)
{
	t_map *map;

	map = &data->map;

	/*
	map->roll = 30;
	map->pitch = 30;
	map->yaw = 30;
	*/
	ft_shape_map(map);
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
	mlx_hook(data->win, 2, 1L<<0, close_window, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
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

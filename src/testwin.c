/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testwin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:10 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/02 13:47:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void testwindow(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_X, WIN_Y, "FdF - by gwolf");
	data->img.img = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bit_per_pixel, &data->img.line_length, &data->img.endian);
	mlx_key_hook(data->win, key_hook, NULL);
	mlx_mouse_hook(data->win, mouse_hook, NULL);
	draw_points(&data->img, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_hook(data->win, 2, 1L<<0, close_window, data);
	mlx_hook(data->win, 6, 1L<<6, mouse_move, data);
	mlx_loop(data->mlx);
}

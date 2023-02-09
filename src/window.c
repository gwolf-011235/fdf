/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:10 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/09 12:50:53 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_window(t_data *data)
{
	int win_x;
	int win_y;

	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &win_x, &win_y);
	ft_printf("Screen size: %d x %d\n", win_x, win_y);
	data->render.ptr = mlx_new_image(data->mlx, win_x, win_y);
	data->render.addr = mlx_get_data_addr(data->render.ptr, &data->render.bpp, &data->render.line_len, &data->render.endian);
	data->render.win_x = win_x;
	data->render.win_y = win_y;
	data->menu.ptr = mlx_new_image(data->mlx, win_x / 6, win_y);
	data->menu.addr = mlx_get_data_addr(data->menu.ptr, &data->menu.bpp, &data->menu.line_len, &data->menu.endian);
	data->menu.win_x = win_x;
	data->menu.win_y = win_y;
	data->map.offset_x = win_x / 2;
	data->map.offset_y = win_y / 2;
	data->win = mlx_new_window(data->mlx, win_x, win_y, "FdF - by gwolf");
}

void testwindow(t_data *data)
{
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
	mlx_key_hook(data->win, key_hook, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook(data->win, 2, 1L<<0, close_window, data);
	mlx_hook(data->win, 6, 1L<<6, mouse_move, data);
	mlx_loop(data->mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:10 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/08 19:11:13 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_window(t_data *data)
{
	int width;
	int height;

	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &width, &height);
	printf("Screen size: %dx%d\n", width, height);
	data->img.img = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bit_per_pixel, &data->img.line_length, &data->img.endian);
	data->win = mlx_new_window(data->mlx, width, height, "FdF - by gwolf");
}

void testwindow(t_data *data)
{
	ft_init_window(data);
	lines(&data->img, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_key_hook(data->win, key_hook, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook(data->win, 2, 1L<<0, close_window, data);
	mlx_hook(data->win, 6, 1L<<6, mouse_move, data);
	mlx_loop(data->mlx);
}

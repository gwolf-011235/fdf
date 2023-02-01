/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testwin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:10 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/01 15:55:06 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void testwindow(t_map *map)
{
	t_vars vars;
	t_data img;
	t_data black;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 600, 400, "Hello World!");
	img.img = mlx_new_image(vars.mlx, 600, 400);
	black.img = mlx_new_image(vars.mlx, 600, 400);
	img.addr = mlx_get_data_addr(img.img, &img.bit_per_pixel, &img.line_length, &img.endian);
	black.addr = mlx_get_data_addr(black.img, &black.bit_per_pixel, &black.line_length, &black.endian);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//fill_background(&black);	
	for (int i = 0; i < 90; i++)
	{
		draw_points(&img, map);
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	(void)map;
	mlx_hook(vars.win, 2, 1L<<0, close_window, &vars);
	mlx_hook(vars.win, 6, 1L<<6, mouse_move, &vars);
	mlx_loop(vars.mlx);
}

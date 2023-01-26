/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testwin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:44:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/26 19:11:40 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void testwindow(void)
{
	t_vars vars;
	t_data img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 600, 500, "Hello World!");
	img.img = mlx_new_image(vars.mlx, 600, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bit_per_pixel, &img.line_length, &img.endian);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	draw_line(&img, 0, 0, 23, 45, create_trgb(0,255, 0, 0));
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, close_window, &vars);
	mlx_hook(vars.win, 6, 1L<<6, mouse_move, &vars);
	mlx_loop(vars.mlx);
}

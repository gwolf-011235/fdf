/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:10 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/25 22:34:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_image(t_data *data, t_img *img, int win_x, int win_y)
{
	img->ptr = mlx_new_image(data->mlx, win_x, win_y);
	if (!img->ptr)
		ft_free_mlx(data, ERR_IMG, true);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, &img->endian);
	img->size[X] = win_x;
	img->size[Y] = win_y;
	img->bytes = img->bpp / 8;
}

void	ft_init_window(t_data *data)
{
	int win_x;
	int win_y;

	data->mlx = mlx_init();
	if (!data->mlx)
		ft_free_mlx(data, ERR_MLX, true);
	mlx_get_screen_size(data->mlx, &win_x, &win_y);
	ft_printf("🖥️  Screen size\n   |%d x %d|\n\n", win_x, win_y);
	data->win = mlx_new_window(data->mlx, win_x, win_y, "FdF - by gwolf");
	if (!data->win)
		ft_free_mlx(data, ERR_WIN, true);
	ft_init_image(data, &data->render, win_x, win_y);
	ft_init_image(data, &data->menu, (win_x / 6), win_y);
	data->map.props.canvas[X] = win_x;
	data->map.props.canvas[Y] = win_y;
	data->map.props.canvas[OFFSET_X] = win_x / 2;
	data->map.props.canvas[OFFSET_Y] = win_y / 2;
}

void testwindow(t_data *data)
{
	//ft_init_menu(data);
	lines(&data->render, &data->map);
	ft_draw_box(&data->render, data->map.edges + 1);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
	mlx_key_hook(data->win, key_hook, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook(data->win, 2, 1L<<0, close_window, data);
	mlx_hook(data->win, 6, 1L<<6, mouse_move, data);
	mlx_loop(data->mlx);
}

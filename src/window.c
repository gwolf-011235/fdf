/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:10 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/12 18:38:57 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_window(t_data *data)
{
	int	*screen;

	screen = data->screen;
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_free_mlx(data, ERR_MLX, true);
	mlx_get_screen_size(data->mlx, &data->screen[X], &data->screen[Y]);
	ft_printf("🖥️  Screen size\n   |%d x %d|\n\n", data->screen[X], data->screen[Y]);
	data->win = mlx_new_window(data->mlx, screen[X], screen[Y], "FdF - by gwolf");
	if (!data->win)
		ft_free_mlx(data, ERR_WIN, true);
	data->render[0] = malloc(sizeof(t_img));
	data->render[1] = malloc(sizeof(t_img));
	ft_init_image(data, data->render[0], screen[X], screen[Y]);
	ft_init_image(data, data->render[1], screen[X] - MENU_WIDTH, screen[Y]);
	printf("0. line_len: %d\n", data->render[0]->line_len);
	printf("1. line_len: %d\n", data->render[1]->line_len);
	ft_init_image(data, &data->menu, MENU_WIDTH, screen[Y]);
	data->map.props.canvas[X] = screen[X];
	data->map.props.canvas[Y] = screen[Y];
	data->map.props.canvas[OFFSET_X] = screen[X] / 2;
	data->map.props.canvas[OFFSET_Y] = screen[Y] / 2;
}

void	ft_init_image(t_data *data, t_img *img, int win_x, int win_y)
{
	img->ptr = mlx_new_image(data->mlx, win_x, win_y);
	if (!img->ptr)
		ft_free_mlx(data, ERR_IMG, true);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, \
			&img->line_len, &img->endian);
	img->bytes = img->bpp / 8;
}

void	ft_start_mlx_loop(t_data *data)
{
	mlx_loop_hook(data->mlx, ft_render, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, ft_key_hook_press, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, \
			ft_mouse_hook_press, data);
	mlx_hook(data->win, ButtonRelease, ButtonReleaseMask, \
			ft_mouse_hook_release, data);
	mlx_hook(data->win, MotionNotify, ButtonMotionMask, \
			ft_mouse_hook_move, data);
	mlx_loop(data->mlx);
}

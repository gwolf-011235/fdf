/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:10 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 15:37:29 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_window(t_data *data)
{
	int	*screen;

	data->mlx = mlx_init();
	if (!data->mlx)
		ft_free_mlx(data, ERR_MLX, true);
	screen = data->screen;
	mlx_get_screen_size(data->mlx, &screen[X], &screen[Y]);
	ft_printf("🖥️  Screen size\n   |%d x %d|\n\n", screen[X], screen[Y]);
	data->win = mlx_new_window(data->mlx, screen[X], screen[Y], "gwolFdF");
	if (!data->win)
		ft_free_mlx(data, ERR_WIN, true);
	ft_init_image(data, &data->render, screen[X], screen[Y]);
	if (data->render.endian)
		ft_printf("🥚 Endian\n   |big|\n\n");
	else
		ft_printf("🥚 Endian\n   |little|\n\n");
	ft_set_canvas_size(data->map.props.canvas, screen[X], screen[Y]);
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
	mlx_hook(data->win, KeyPress, KeyPressMask, ft_key_hook_press, data);
	mlx_hook(data->win, 17, 1L << 17, ft_close_program, data);
	mlx_loop(data->mlx);
}

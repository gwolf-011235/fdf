/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:10 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 17:39:24 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_init_menu(t_data *data)
{
	static const char	files[3][20] = {
		"assets/menu.xpm",
		"assets/controls.xpm",
		"assets/layer.xpm"};
	int					x;
	int					y;

	data->menu[0]->ptr = mlx_xpm_file_to_image(data->mlx,
			(char *)files[0], &x, &y);
	if (data->menu[0]->ptr == NULL)
		ft_free_mlx(data, (char *)files[0], true);
	data->menu[1]->ptr = mlx_xpm_file_to_image(data->mlx,
			(char *)files[1], &x, &y);
	if (data->menu[1]->ptr == NULL)
		ft_free_mlx(data, (char *)files[1], true);
	data->menu[2]->ptr = mlx_xpm_file_to_image(data->mlx,
			(char *)files[2], &x, &y);
	if (data->menu[2]->ptr == NULL)
		ft_free_mlx(data, (char *)files[2], true);
	mlx_set_font(data->mlx, data->win,
		"-misc-fixed-medium-r-normal-*-15-*-*-100-*-*-iso8859-1");
}

void	ft_set_img_ptr(t_img *images, t_img *render[2], t_img *menu[3])
{
	render[0] = images;
	render[1] = images + 1;
	menu[0] = images + 2;
	menu[1] = images + 3;
	menu[2] = images + 4;
}

void	ft_init_window(t_data *data)
{
	int	*screen;

	data->images = malloc(sizeof(t_img) * 5);
	if (!data->images)
		ft_free_mlx(data, ERR_MEM, true);
	ft_set_img_ptr(data->images, data->render, data->menu);
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_free_mlx(data, ERR_MLX, true);
	screen = data->screen;
	mlx_get_screen_size(data->mlx, &screen[X], &screen[Y]);
	ft_printf("🖥️  Screen size\n   |%d x %d|\n\n", screen[X], screen[Y]);
	data->win = mlx_new_window(data->mlx, screen[X], screen[Y], "gwolFdF");
	if (!data->win)
		ft_free_mlx(data, ERR_WIN, true);
	ft_init_image(data, data->render[0], screen[X], screen[Y]);
	if (data->render[0]->endian)
		ft_printf("🥚 Endian\n   |big|\n\n");
	else
		ft_printf("🥚 Endian\n   |little|\n\n");
	ft_init_image(data, data->render[1], screen[X] - MENU_WIDTH, screen[Y]);
	ft_init_menu(data);
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
	mlx_loop_hook(data->mlx, ft_render, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, ft_key_hook_press, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, \
			ft_mouse_hook_press, data);
	mlx_hook(data->win, ButtonRelease, ButtonReleaseMask, \
			ft_mouse_hook_release, data);
	mlx_hook(data->win, MotionNotify, ButtonMotionMask, \
			ft_mouse_hook_move, data);
	mlx_hook(data->win, 17, 1L << 17, ft_close_program, data);
	mlx_loop(data->mlx);
}

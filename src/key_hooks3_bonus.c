/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:01 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 14:58:23 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_key_ftptr(int key, t_data *data)
{
	static bool	calc;
	static bool	draw;

	if (key == KEY_ENTER)
	{
		calc = !calc;
		if (calc)
			ft_set_ft_ptr(data, 1);
		else
			ft_set_ft_ptr(data, 0);
	}
	if (key == KEY_J)
	{
		draw = !draw;
		if (draw)
			ft_set_ft_ptr(data, 3);
		else
			ft_set_ft_ptr(data, 2);
	}
}

void	ft_key_sampling(int key, t_map *map)
{
	if (key == KEY_K)
	{
		map->sampling--;
		if (!map->sampling)
			map->sampling = 1;
	}
	if (key == KEY_L)
	{
		map->sampling++;
		if (map->sampling >= 9)
			map->sampling = 9;
	}
}

void	ft_key_toggle_menu(t_data *data)
{
	if (data->map.menu == OFF)
		data->map.menu = STATS;
	else if (data->map.menu == CONTROL)
	{
		ft_swap_img_ptr(&data->menu[0], &data->menu[1]);
		data->map.menu = OFF;
	}
	else
		data->map.menu = OFF;
	if (data->map.menu)
	{
		ft_swap_img_ptr(&data->render[0], &data->render[1]);
		data->map.menu_width = MENU_WIDTH;
		ft_set_canvas_size(data->map.props.canvas, -MENU_WIDTH, 0);
		mlx_put_image_to_window(data->mlx, data->win, data->menu[0]->ptr, 0, 0);
		if (data->map.menu == STATS)
			ft_write_menu(data);
	}
	else
	{
		ft_swap_img_ptr(&data->render[0], &data->render[1]);
		data->map.menu_width = 0;
		ft_set_canvas_size(data->map.props.canvas, MENU_WIDTH, 0);
	}
}

void	ft_key_toggle_controls(t_data *data)
{
	if (data->map.menu == OFF)
		return ;
	else if (data->map.menu == STATS)
		data->map.menu = CONTROL;
	else
		data->map.menu = STATS;
	ft_swap_img_ptr(&data->menu[0], &data->menu[1]);
	mlx_put_image_to_window(data->mlx, data->win, data->menu[0]->ptr, 0, 0);
	if (data->map.menu == STATS)
		ft_write_menu(data);
}

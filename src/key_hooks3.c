/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:01 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/12 22:57:47 by gwolf            ###   ########.fr       */
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

void	ft_key_skip(int key, t_map *map)
{
	if (key == KEY_K)
	{
		map->skip--;
		if (!map->skip)
			map->skip = 1;
	}
	if (key == KEY_L)
	{
		map->skip++;
		if (map->skip >= 10)
			map->skip = 10;
	}
}

void	ft_key_menu(t_data *data)
{
	data->map.menu = !data->map.menu;
	if (data->map.menu)
	{
		ft_swap_img_ptr(&data->render[0], &data->render[1]);
		data->map.menu_width = MENU_WIDTH;
		data->map.props.canvas[X] -= MENU_WIDTH;
		data->map.props.canvas[OFFSET_X] = data->map.props.canvas[X] / 2;
		mlx_put_image_to_window(data->mlx, data->win, data->menu[0]->ptr, 0, 0);
		ft_write_menu(data);
	}
	else
	{
		ft_swap_img_ptr(&data->render[0], &data->render[1]);
		data->map.menu_width = 0;
		data->map.props.canvas[X] += MENU_WIDTH;
		data->map.props.canvas[OFFSET_X] = data->map.props.canvas[X] / 2;
	}
}

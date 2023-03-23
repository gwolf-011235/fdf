/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:39:39 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 14:59:41 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_key_hook_press(int key, t_data *data)
{
	if ((key >= KEY_ARROW_LEFT && key <= KEY_ARROW_DOWN) || key == KEY_W
		|| key == KEY_S || key == KEY_A || key == KEY_D || key == KEY_Q
		|| key == KEY_E || key == KEY_R || key == KEY_F || key == KEY_X
		|| key == KEY_C || key == KEY_ONE || key == KEY_TWO || key == KEY_THREE
		|| key == KEY_FOUR || key == KEY_FIVE || key == KEY_SPACE
		|| key == KEY_SIX || key == KEY_SEVEN || key == KEY_EIGHT
		|| key == KEY_NINE || key == KEY_ZERO)
		ft_key_press_handler1(key, &data->map);
	if (key == KEY_B || key == KEY_N || key == KEY_M
		|| key == KEY_G || key == KEY_J || key == KEY_ENTER || key == KEY_K
		|| key == KEY_L || key == KEY_I || key == KEY_H || key == KEY_ESC)
		ft_key_press_handler2(key, data);
	return (0);
}

void	ft_key_press_handler1(int key, t_map *map)
{
	if (key >= KEY_ARROW_LEFT && key <= KEY_ARROW_DOWN)
		ft_key_translate(key, map);
	else if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		ft_key_rotate_xy(key, map);
	else if (key == KEY_Q || key == KEY_E)
		ft_key_rotate_z(key, map);
	else if (key == KEY_R || key == KEY_F || key == KEY_ZERO)
		ft_key_zoom(key, map);
	else if (key == KEY_X || key == KEY_C)
		ft_key_scale(key, map);
	else if (key == KEY_ONE || key == KEY_TWO || key == KEY_THREE
		|| key == KEY_FOUR || key == KEY_FIVE)
		ft_key_color(key, map);
	else if (key == KEY_SPACE)
		ft_key_sphere(key, map);
	else if (key == KEY_SIX || key == KEY_SEVEN || key == KEY_EIGHT
		|| key == KEY_NINE)
		ft_key_view(key, map);
}

void	ft_key_press_handler2(int key, t_data *data)
{
	if (key == KEY_B || key == KEY_N || key == KEY_M
		|| key == KEY_G)
		ft_key_stuff(key, &data->map);
	else if (key == KEY_J || key == KEY_ENTER)
		ft_key_ftptr(key, data);
	else if (key == KEY_K || key == KEY_L)
		ft_key_sampling(key, &data->map);
	else if (key == KEY_I)
		ft_key_toggle_menu(data);
	else if (key == KEY_H)
		ft_key_toggle_controls(data);
	else if (key == KEY_ESC)
		ft_close_program(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:16:59 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/15 18:47:30 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	ft_key_hook_press(int key, t_data *data)
{
	if ((key >= KEY_ARROW_LEFT && key <= KEY_ARROW_DOWN) || key == KEY_W 
		|| key == KEY_S || key == KEY_A || key == KEY_D || key == KEY_Q
		|| key == KEY_E || key == KEY_R || key == KEY_F || key == KEY_X
		|| key == KEY_C || key == KEY_ONE || key == KEY_TWO || key == KEY_THREE
		|| key == KEY_FOUR || key == KEY_FIVE || key == KEY_SPACE
		|| key == KEY_SIX || key == KEY_SEVEN || key == KEY_EIGHT
		|| key == KEY_NINE || key == KEY_ZERO)
		ft_key_hook_press2(key, &data->map);
	else if (key == KEY_B || key == KEY_N || key == KEY_M
		|| key == KEY_G || key == KEY_ESC)
		ft_key_stuff(key, &data->map, data);
	else if (key == KEY_J || key == KEY_ENTER)
		ft_key_ftptr(key, data);
	else if (key == KEY_K || key == KEY_L)
		ft_key_skip(key, &data->map);
	else if (key == KEY_I)
		ft_key_toggle_menu(data);
	else if (key == KEY_H)
		ft_key_toggle_controls(data);
	return (0);
}

void	ft_key_hook_press2(int key, t_map *map)
{
	if (key >= KEY_ARROW_LEFT && key <= KEY_ARROW_DOWN)
		ft_key_translate(key, map);
	else if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		ft_key_angle(key, map);
	else if (key == KEY_Q || key == KEY_E)
		ft_key_angle2(key, map);
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


void	ft_key_translate(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_ARROW_LEFT)
	{
		map->props.translate[X] -= factor;
		map->mat[3][0] -= factor;
	}
	else if (key == KEY_ARROW_RIGHT)
	{
		map->props.translate[X] += factor;
		map->mat[3][0] += factor;
	}
	else if (key == KEY_ARROW_UP)
	{
		map->props.translate[Y] -= factor;
		map->mat[3][1] -= factor;
	}
	else if (key == KEY_ARROW_DOWN)
	{
		map->props.translate[Y] += factor;
		map->mat[3][1] += factor;
	}
}

void	ft_key_angle(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_S)
	{
		map->props.angle[X] = ft_wrap_angle(map->props.angle[X], -factor);
		ft_precalc_rot_x(map->mat, factor);
	}
	else if (key == KEY_W)
	{
		map->props.angle[X] = ft_wrap_angle(map->props.angle[X], factor);
		ft_precalc_rot_x(map->mat, factor -1);
	}
	else if (key == KEY_A)
	{
		map->props.angle[Y] = ft_wrap_angle(map->props.angle[Y], -factor);
		ft_precalc_rot_y(map->mat, factor);
	}
	else if (key == KEY_D)
	{
		map->props.angle[Y] = ft_wrap_angle(map->props.angle[Y], factor);
		ft_precalc_rot_y(map->mat, factor - 1);
	}
}

void	ft_key_angle2(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_Q)
	{
		map->props.angle[Z] = ft_wrap_angle(map->props.angle[Z], -factor);
		ft_precalc_rot_z(map->mat, factor);
	}
	else if (key == KEY_E)
	{
		map->props.angle[Z] = ft_wrap_angle(map->props.angle[Z], factor);
		ft_precalc_rot_z(map->mat, factor - 1);
	}
}

void	ft_key_zoom(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_R)
	{
		if (map->props.scale >= 1000)
			return ;
		map->props.scale *= 1 + 0.1 * factor;
		ft_precalc_zoom(map->mat, factor - 1);
	}
	else if (key == KEY_F)
	{
		if (map->props.scale <= 0)
			return ;
		map->props.scale *= 1 - 0.1 * factor;
		ft_precalc_zoom(map->mat, factor);
	}
	else if (key == KEY_ZERO)
	{
		map->props.translate[X] = 0;
		map->props.translate[Y] = 0;
		map->props.scale = ft_fit_box(map->edges, map->mat, map->props);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:16:59 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/09 19:19:23 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	ft_key_hook_press(int key, t_data *data)
{
	if (key >= KEY_ARROW_LEFT && key <= KEY_ARROW_DOWN)
		ft_key_translate(key, &data->map);
	else if (key == KEY_A || key == KEY_S || key == KEY_D || key == KEY_F)
		ft_key_angle(key, &data->map);
	else if (key == KEY_G || key == KEY_H)
		ft_key_angle2(key, &data->map);
	else if (key == KEY_Q || key == KEY_W)
		ft_key_zoom(key, &data->map);
	else if (key == KEY_E || key == KEY_R)
		ft_key_scale(key, &data->map);
	else if (key == KEY_ONE || key == KEY_TWO || key == KEY_THREE
		|| key == KEY_FOUR || key == KEY_FIVE)
		ft_key_color(key, &data->map);
	else if (key == KEY_SPACE)
		ft_key_sphere(key, &data->map);
	else if (key == KEY_SIX || key == KEY_SEVEN || key == KEY_EIGHT
		|| key == KEY_NINE)
		ft_key_view(key, &data->map);
	else if (key == KEY_B || key == KEY_PLUS || key == KEY_MINUS || key == KEY_ESC)
		ft_key_stuff(key, &data->map, data);
	return (0);
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
	if (key == KEY_A)
	{
		map->props.angle[X] -= factor;
		ft_precalc_rot_x(map->mat, factor);
	}
	else if (key == KEY_S)
	{
		map->props.angle[X] += factor;
		ft_precalc_rot_x(map->mat, factor -1);
	}
	else if (key == KEY_D)
	{
		map->props.angle[Y] -= factor;
		ft_precalc_rot_y(map->mat, factor);
	}
	else if (key == KEY_F)
	{
		map->props.angle[Y] += factor;
		ft_precalc_rot_y(map->mat, factor - 1);
	}
}

void	ft_key_angle2(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_G)
	{
		map->props.angle[Z] -= factor;
		ft_precalc_rot_z(map->mat, factor);
	}
	else if (key == KEY_H)
	{
		map->props.angle[Z] += factor;
		ft_precalc_rot_z(map->mat, factor - 1);
	}
}

void	ft_key_zoom(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_Q)
	{
		map->props.scale *= 1 + 0.1 * factor;
		ft_precalc_zoom(map->mat, factor - 1);
	}
	else if (key == KEY_W)
	{
		map->props.scale *= 1 - 0.1 * factor;
		ft_precalc_zoom(map->mat, factor);
	}
}

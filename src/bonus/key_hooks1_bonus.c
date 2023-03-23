/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:16:59 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/17 16:40:35 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "mlx.h"

void	ft_key_translate(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_ARROW_LEFT && map->props.translate[X] > -5000)
	{
		map->props.translate[X] -= factor;
		map->mat[3][0] -= factor;
	}
	else if (key == KEY_ARROW_RIGHT && map->props.translate[X] < 5000)
	{
		map->props.translate[X] += factor;
		map->mat[3][0] += factor;
	}
	else if (key == KEY_ARROW_UP && map->props.translate[Y] > -5000)
	{
		map->props.translate[Y] -= factor;
		map->mat[3][1] -= factor;
	}
	else if (key == KEY_ARROW_DOWN && map->props.translate[Y] < 5000)
	{
		map->props.translate[Y] += factor;
		map->mat[3][1] += factor;
	}
}

void	ft_key_rotate_xy(int key, t_map *map)
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

void	ft_key_rotate_z(int key, t_map *map)
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
	if (key == KEY_R && map->props.scale < 1000)
	{
		map->props.scale *= 1 + 0.1 * factor;
		ft_precalc_zoom(map->mat, factor - 1);
	}
	else if (key == KEY_F && map->props.scale > 0.1)
	{
		map->props.scale *= 1 - 0.1 * factor;
		ft_precalc_zoom(map->mat, factor);
	}
	else if (key == KEY_ZERO)
	{
		map->props.translate[X] = 0;
		map->props.translate[Y] = 0;
		map->props.scale = ft_fit_box(map->corner[0], map->mat, map->props);
	}
}

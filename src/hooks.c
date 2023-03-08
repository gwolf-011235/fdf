/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:16:59 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/08 19:06:32 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	key_hook(int key, t_data *data)
{
	if (key == KEY_A || key == KEY_S || key == KEY_D || key == KEY_F
		|| key == KEY_G || key == KEY_H)
		ft_key_angle(key, &data->map);
	else if (key == KEY_Q || key == KEY_W || key == KEY_E || key == KEY_R)
		ft_key_scale(key, &data->map);
	else if (key >= KEY_ARROW_LEFT && key <= KEY_ARROW_DOWN)
		ft_key_translate(key, &data->map);
	else if (key == KEY_ONE || key == KEY_TWO || key == KEY_THREE
		|| key == KEY_FOUR || key == KEY_FIVE)
		ft_key_color(key, &data->map);
	else if (key == KEY_SPACE || key == KEY_B || key == KEY_PLUS
		|| key == KEY_MINUS)
		ft_key_sphere(key, &data->map);
	else if (key == KEY_ESC)
	{
		ft_free_mlx(data, CYA, false);
		exit(0);
	}
	printf("This is key: %d\n", key);
	return (0);
}

void	ft_key_sphere(int key, t_map *map)
{
	if (key == KEY_SPACE)
	{
		map->props.sphere = !map->props.sphere;
		if (map->props.sphere)
			ft_calc_sphere_points(map, map->ang_coord, map->polar);
		else
		{
			ft_scale_z(map->points, map->z_storage, map->sum_points, map->props.scale_z);
			ft_set_limits_xy(map);
			ft_find_limits_z(map);
		}
	}
	else if (key == KEY_B)
	{
		map->props.box = !map->props.box;
	}
	else if (key == KEY_PLUS)
	{
		if (map->factor == 1)
			map->factor = 3;
		else if (map->factor == 3)
			map->factor = 5;
	}
	else if (key == KEY_MINUS)
	{
		if (map->factor == 5)
			map->factor = 3;
		else if (map->factor == 3)
			map->factor = 1;
	}
}

int	ft_wrap_angle(float angle, int factor)
{
	angle += factor;
	if (angle < 0)
		angle = 360 - factor;
	if (angle > 360)
		angle = 0 + factor;
	return (angle);
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
	else if (key == KEY_G)
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

void	ft_key_scale(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_Q)
	{
		map->props.scale += 0.1 * factor;
		ft_precalc_zoom(map->mat, factor - 1);
	}
	else if (key == KEY_W)
	{
		map->props.scale -= 0.1 * factor;
		ft_precalc_zoom(map->mat, factor);
	}
	else if (key == KEY_E)
	{
		map->props.scale_z -= 0.1 * factor;
		if (!map->props.sphere)
			ft_scale_z(map->points, map->z_storage, map->sum_points, \
				map->props.scale_z);
		else
			ft_calc_sphere_points(map, map->ang_coord, map->polar);
	}
	else if (key == KEY_R)
	{
		map->props.scale_z += 0.1 * factor;
		if (!map->props.sphere)
			ft_scale_z(map->points, map->z_storage, map->sum_points, \
				map->props.scale_z);
		else
			ft_calc_sphere_points(map, map->ang_coord, map->polar);
	}
}

void	ft_key_color(int key, t_map *map)
{
	int	specific;

	specific = 5;
	if (map->select)
		specific = key;
	if (key == KEY_ONE)
		ft_set_pattern(map->pattern, 0, specific);
	else if (key == KEY_TWO)
		ft_set_pattern(map->pattern, 1, specific);
	else if (key == KEY_THREE)
		ft_set_pattern(map->pattern, 2, specific);
	else if (key == KEY_FOUR)
		ft_set_pattern(map->pattern, 3, specific);
	else if (key == KEY_FIVE)
		map->select = !map->select;
	ft_set_colors(map, map->points);
}

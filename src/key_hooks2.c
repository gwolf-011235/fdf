/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:01:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/10 16:44:16 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_key_scale(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_X)
	{
		map->props.scale_z -= 0.1 * factor;
		if (!map->props.sphere)
			ft_scale_z(map->points, map->z_storage, map->sum_points, \
				map->props.scale_z);
		else
			ft_calc_sphere_points(map, map->ang_coord, map->polar);
	}
	else if (key == KEY_C)
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
	if (key == KEY_ONE)
		ft_set_pattern(map->pattern, 0);
	else if (key == KEY_TWO)
		ft_set_pattern(map->pattern, 1);
	else if (key == KEY_THREE)
		ft_set_pattern(map->pattern, 2);
	else if (key == KEY_FOUR)
		ft_set_pattern(map->pattern, 3);
	else if (key == KEY_FIVE)
		ft_set_pattern(map->pattern, 4);
	ft_find_limits_z(map);
	ft_set_colors(map, map->points);
	ft_set_morph_color(map->morph, map->points, map->sum_points);
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
			ft_scale_z(map->points, map->z_storage,
				map->sum_points, map->props.scale_z);
			ft_set_limits_xy(map);
			ft_find_limits_z(map);
		}
	}
}

void	ft_key_view(int key, t_map *map)
{
	if (key == KEY_SIX)
	{
		map->props.view = 1;
		ft_build_transmat(map->mat, map->props);
	}
	if (key == KEY_SEVEN)
	{
		map->props.view = 2;
		ft_build_transmat(map->mat, map->props);
	}
	if (key == KEY_EIGHT)
	{
		map->props.view = 3;
		ft_build_transmat(map->mat, map->props);
	}
	if (key == KEY_NINE)
	{
		map->props.view = 4;
		ft_build_transmat(map->mat, map->props);
	}
}

void	ft_key_stuff(int key, t_map *map, t_data *data)
{
	if (key == KEY_B)
	{
		map->props.box = !map->props.box;
	}
	else if (key == KEY_M)
	{
		if (map->factor == 1)
			map->factor = 3;
		else if (map->factor == 3)
			map->factor = 5;
	}
	else if (key == KEY_N)
	{
		if (map->factor == 5)
			map->factor = 3;
		else if (map->factor == 3)
			map->factor = 1;
	}
	else if (key == KEY_ESC)
	{
		ft_free_mlx(data, CYA, false);
		exit(0);
	}
}

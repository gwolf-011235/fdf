/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:01:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 14:22:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_key_scale(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_X)
	{
		if (map->props.scale_z <= -10.0)
			return ;
		map->props.scale_z -= 0.1 * factor;
		if (!map->props.sphere)
			ft_scale_z(map->points, map->z_storage, map->sum_points, \
				map->props.scale_z);
		else
			ft_calc_sphere_points(map, map->lonlat, map->polar);
	}
	else if (key == KEY_C)
	{
		if (map->props.scale_z >= 10.0)
			return ;
		map->props.scale_z += 0.1 * factor;
		if (!map->props.sphere)
			ft_scale_z(map->points, map->z_storage, map->sum_points, \
				map->props.scale_z);
		else
			ft_calc_sphere_points(map, map->lonlat, map->polar);
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
	ft_set_morph_color(map->points, map->morph, map);
}

void	ft_key_sphere(int key, t_map *map)
{
	if (key == KEY_SPACE)
	{
		map->props.sphere = !map->props.sphere;
		if (map->props.sphere)
			ft_calc_sphere_points(map, map->lonlat, map->polar);
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
		map->props.view = ISO;
		ft_set_view_angles(map->props.angle, ISO);
	}
	else if (key == KEY_SEVEN)
	{
		map->props.view = TOP;
		ft_set_view_angles(map->props.angle, TOP);
	}
	else if (key == KEY_EIGHT)
	{
		map->props.view = SIDE;
		ft_set_view_angles(map->props.angle, SIDE);
	}
	else if (key == KEY_NINE)
	{
		map->props.view = NICE;
		ft_set_view_angles(map->props.angle, NICE);
	}
	ft_build_transmat(map->mat, map->props);
}

void	ft_key_stuff(int key, t_map *map)
{
	if (key == KEY_B)
		map->props.box = !map->props.box;
	else if (key == KEY_G)
		map->rainbow = !map->rainbow;
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
}

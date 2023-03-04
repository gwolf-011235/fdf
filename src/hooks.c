/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:16:59 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/04 21:46:15 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int key_hook(int key, t_data *data)
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
	else if (key == KEY_ESC)
	{
		ft_free_mlx(data, CYA, false);
		exit(0);
	}
	ft_redraw(data);
	usleep(16667);
	printf("This is key: %d\n", key);
	return (0);
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
	int factor;

	factor = map->factor;
	if (key == KEY_ARROW_LEFT)
		map->props.translate[X] -= factor;
	else if (key == KEY_ARROW_RIGHT)
		map->props.translate[X] += factor;
	else if (key == KEY_ARROW_UP)
		map->props.translate[Y] -= factor;
	else if (key == KEY_ARROW_DOWN)
		map->props.translate[Y] += factor;
}

void	ft_key_angle(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_A)
		map->props.angle[X] -= factor;
	else if (key == KEY_S)
		map->props.angle[X] += factor;
	else if (key == KEY_D)
		map->props.angle[Y] -= factor;
	else if (key == KEY_F)
		map->props.angle[Y] += factor;
	else if (key == KEY_G)
		map->props.angle[Z] -= factor;
	else if (key == KEY_H)
		map->props.angle[Z] += factor;
}

void	ft_key_scale(int key, t_map *map)
{
	int	factor;

	factor = map->factor;
	if (key == KEY_Q)
		map->props.scale += 0.1 * factor;
	else if (key == KEY_W)
		map->props.scale -= 0.1 * factor;
	else if (key == KEY_E)
	{
		map->props.scale_z -= 0.1 * factor;
		ft_scale_z(map->points, map->z_storage, map->sum_points, \
				map->props.scale_z);
		if (map->props.sphere)
			ft_calc_sphere_points(map, map->ang_coord, map->polar);
	}
	else if (key == KEY_R)
	{
		map->props.scale_z += 0.1 * factor;
		ft_scale_z(map->points, map->z_storage, map->sum_points, \
				map->props.scale_z);
		if (map->props.sphere)
			ft_calc_sphere_points(map, map->ang_coord, map->polar);
	}
}

void	ft_key_color(int key, t_map *map)
{
	int specific;

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

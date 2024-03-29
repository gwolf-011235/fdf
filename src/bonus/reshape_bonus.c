/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/29 11:27:25 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_init_projection(t_data *data)
{
	t_map	*map;

	map = &data->map;
	ft_set_morph_color(map->points, map->morph, map);
	ft_scale_z(map->points, map->z_storage, map->sum_points, 0.1);
	map->props.scale = ft_fit_box(map->corner[0], map->mat, map->props);
	ft_calc_morph(map->morph, map->points, map->mat, map);
	ft_check_visible(map->morph, map->sum_points, map->props.canvas);
	ft_draw_wirelines(data->render[0], &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render[0]->ptr, 0, 0);
}

void	ft_scale_z(t_vec3f *points, int *z_storage, int sum, float scale_z)
{
	int	i;

	i = 0;
	while (i < sum + 8)
	{
		points[i].z = z_storage[i] * scale_z;
		i++;
	}
}

void	ft_calc_morph(t_vec3f *morph, t_vec3f *points, t_mat4 mat, t_map *map)
{
	int		i;

	i = 0;
	while (i < map->sum_points + 8)
	{
		morph[i].x = points[i].x * mat[0][0] + points[i].y * mat[1][0]
			+ points[i].z * mat[2][0] + mat[3][0];
		morph[i].y = points[i].x * mat[0][1] + points[i].y * mat[1][1]
			+ points[i].z * mat[2][1] + mat[3][1];
		morph[i].z = points[i].x * mat[0][2] + points[i].y * mat[1][2]
			+ points[i].z * mat[2][2] + mat[3][2];
		i++;
	}
}

void	ft_check_visible(t_vec3f *morph, int sum_points, int size[2])
{
	int	i;

	i = 0;
	while (i < sum_points + 8)
	{
		if (morph[i].x < 0 || morph[i].x > size[X]
			|| morph[i].y < 0 || morph[i].y > size[Y])
			morph[i].hidden = true;
		else
			morph[i].hidden = false;
		i++;
	}
}

int	ft_render(t_data *data)
{
	t_map			*map;

	if (ft_check_fps(data))
		return (0);
	map = &data->map;
	fill_background(data->render[0], data->map.pattern[3],
		data->map.props.canvas);
	if (!map->props.sphere)
		data->calc_ft(map->morph, map->points, map->mat, map);
	else
		data->calc_ft(map->morph, map->sphere, map->mat, map);
	ft_check_visible(map->morph, map->sum_points, map->props.canvas);
	if (data->map.props.rainbow)
		ft_skittles(&data->map, data->map.morph);
	data->draw_ft(data->render[0], map);
	if (map->props.box)
		ft_draw_box(data->render[0], map->corner[1], data->map.props.canvas);
	mlx_put_image_to_window(data->mlx, data->win,
		data->render[0]->ptr, data->map.menu_width, 0);
	if (map->menu == OFF)
		mlx_string_put(data->mlx, data->win, 10, 20, WHITE,
			"Press 'I' for menu");
	else if (map->menu == STATS)
		ft_update_menu(data);
	return (0);
}

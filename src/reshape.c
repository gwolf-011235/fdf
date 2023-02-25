/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/24 22:22:23 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_calc_points(t_vec3f *points, t_mat4 mat, int sum, int size[2])
{
	int		i;
	t_vec3f	*morph;

	morph = points + 1;
	i = 0;
	while (i < sum)
	{
		morph[i + i] = ft_mult_vec3f_mat4(points[i + i], mat);
		morph[i + i].color = points[i + i].color;
		morph[i + i].hidden = ft_is_outside(morph[i + i], size, 0);
		i++;
	}
	while (i < (sum + 8))
	{
		morph[i + i] = ft_mult_vec3f_mat4(points[i + i], mat);
		i++;
	}
}

void	ft_init_project(t_map *map, int size[2])
{
	map->props.scale = ft_fit_box(map->edges, map->mat, map->props);
	ft_calc_points(map->points, map->mat, map->sum_points, size);
	ft_init_pixel(map->points + 1, map->pixel, map->sum_points);
}

void	ft_redraw(t_data *data)
{
	ft_build_transmat(data->map.mat, data->map.props);
	ft_calc_points(data->map.points, data->map.mat, data->map.sum_points, data->render.size);
	ft_init_pixel(data->map.points + 1, data->map.pixel, data->map.sum_points);
	fill_background(&data->render, data->map.pattern[3]);
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
}

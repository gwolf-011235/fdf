/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/24 17:14:48 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_calc_points(t_vec3f *points, t_mat4 mat, int sum)
{
	int		i;
	t_vec3f	*morph;

	morph = points + 1;
	i = 0;
	while (i < sum)
	{
		morph[i D] = ft_mult_vec3f_mat4(points[i D], mat);
		i++;
	}
	while (i < (sum + 8))
	{
		morph[i D] = ft_mult_vec3f_mat4(points[i D], mat);
		i++;
	}
}

void	ft_init_project(t_map *map)
{
	map->props.scale = ft_fit_box(map->edges, map->mat, map->props);
	ft_calc_points(map->points, map->mat, map->sum_points);
	ft_init_pixel(map->points + 1, map->colors, map->pixel, map->sum_points);
}

void	ft_redraw(t_data *data)
{
	ft_build_transmat(data->map.mat, data->map.props);
	ft_calc_points(data->map.points, data->map.mat, data->map.sum_points);
	ft_init_pixel(data->map.points + 1, data->map.colors, data->map.pixel, data->map.sum_points);
	fill_background(&data->render, data->map.pattern[3]);
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
}

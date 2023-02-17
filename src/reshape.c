/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/17 10:15:31 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_pixel(t_vec3f *morph, int *colors, t_point *pixel, int sum)
{
	int	i;

	i = 0;
	while (i < sum)
	{
		pixel[i] = ft_convert_vec2point(morph[i + i], colors[i]);
		i++;
	}
	while (i < (sum + 8))
	{
		pixel[i] = ft_convert_vec2point(morph[i + i], RED);
		i++;
	}
}

void	ft_calc_points(t_vec3f *points, t_mat4 trans, int sum)
{
	int		i;
	t_vec3f	*morph;

	morph = points + 1;
	i = 0;
	while (i < sum)
	{
		morph[i D] = ft_mult_vec3f_mat4(points[i D], trans);
		i++;
	}
	while (i < (sum + 8))
	{
		morph[i D] = ft_mult_vec3f_mat4(points[i D], trans);
		i++;
	}
}

void	ft_init_transmat(t_map *map)
{
	//ft_const_iso(map->trans);
	ft_init_mat4(map->trans);
	map->trans[0][0] = 1;
	map->trans[1][1] = 1;
	map->trans[2][2] = 1;
	map->trans[0][0] *= map->scale;
	map->trans[1][1] *= map->scale;
	map->trans[2][2] *= map->scale;
	map->trans[3][3] = 1;
	map->trans[3][0] = map->offset[X];
	map->trans[3][1] = map->offset[Y];
}

void	ft_init_project(t_map *map)
{
	ft_init_transmat(map);
	ft_calc_points(map->points, map->trans, map->sum_points);
	ft_init_pixel(map->points + 1, map->colors, map->pixel, map->sum_points);
}

void	ft_shape_map(t_map *map) //init trans or smth
{
	ft_init_mat4(map->trans);
	map->trans[0][0] = map->scale;
	map->trans[1][1] = map->scale;
	map->trans[2][2] = map->scale;
	map->trans[3][3] = 1;
	ft_rotate_x(map->trans, map->roll);
	ft_rotate_y(map->trans, map->pitch);
	ft_rotate_z(map->trans, map->yaw);
	map->trans[3][0] = map->trans_x + map->offset[X];
	map->trans[3][1] = map->trans_y + map->offset[Y];
}

void	ft_redraw(t_data *data)
{
	ft_shape_map(&data->map);
	ft_calc_points(data->map.points, data->map.trans, data->map.sum_points);
	ft_init_pixel(data->map.points + 1, data->map.colors, data->map.pixel, data->map.sum_points);
	fill_background(&data->render);
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
}

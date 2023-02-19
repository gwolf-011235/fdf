/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/19 07:36:39 by gwolf            ###   ########.fr       */
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

void	ft_update_pix_point(t_vec3f *morph, t_point *pixel, int sum)
{
	int	i;

	i = 0;
	while (i < (sum + 8))
	{
		pixel[i].x = floor(morph[i + i].x);
		pixel[i].y = floor(morph[i + i].y);
		i++;
	}
}

void	ft_update_pix_color(int *colors, t_point *pixel, int sum)
{
	int	i;

	i = 0;
	while (i < sum)
	{
		pixel[i].color = colors[i];
		i++;
	}
}

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

void	ft_shape_map(t_map *map) //init trans or smth
{
	ft_init_mat4(map->mat);
	map->mat[0][0] = map->scale;
	map->mat[1][1] = map->scale;
	map->mat[2][2] = map->scale;
	map->mat[3][3] = 1;
	ft_rotate_x(map->mat, map->roll);
	ft_rotate_y(map->mat, map->pitch);
	ft_rotate_z(map->mat, map->yaw);
	map->mat[3][0] = map->trans_x + map->offset[X];
	map->mat[3][1] = map->trans_y + map->offset[Y];
}

void	ft_redraw(t_data *data)
{
	ft_build_transmat(data->map.mat, data->map.props);
	ft_calc_points(data->map.points, data->map.mat, data->map.sum_points);
	ft_init_pixel(data->map.points + 1, data->map.colors, data->map.pixel, data->map.sum_points);
	fill_background(&data->render);
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
}

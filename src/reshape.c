/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/05 07:45:46 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_calc_edges(t_vec3f *edges, t_mat4 mat, int size[2])
{
	int		i;
	t_vec3f	*m_edges;

	m_edges = edges + 8;
	i = 0;
	while (i < 8)
	{
		m_edges[i] = ft_mult_vec3f_mat4(edges[i], mat);
		m_edges[i].hidden = ft_is_outside(edges[i], size, 0);
		i++;
	}
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

void	ft_calc_points(t_map *map, t_vec3f *points, int size[2])
{
	int		i;

	i = 0;
	while (i < map->sum_points + 8)
	{
 		map->morph[i] = ft_mult_vec3f_mat4(points[i], map->mat);
		map->morph[i].color = points[i].color;
		map->morph[i].hidden = ft_is_outside(map->morph[i], size, 0);
		i++;
	}
}

void	ft_init_project(t_data *data)
{
	t_map *map;

	map = &data->map;
	ft_scale_z(map->points, map->z_storage, map->sum_points, 0.1);
	data->map.props.iso = true;	
	map->props.scale = ft_fit_box(map->edges, map->mat, map->props);
	data->map.props.iso = false;
	ft_calc_points(map, map->points, data->render.size);
	lines(&data->render, &data->map);
	ft_draw_box(&data->render, data->map.corner[1]);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
}

int	ft_redraw(t_data *data)
{
	clock_t t;
	double ret;

	t = clock();
	fill_background(&data->render, data->map.pattern[3]);
	ft_build_transmat(data->map.mat, data->map.props);
	if (!data->map.props.sphere)
		ft_calc_points(&data->map, data->map.points, data->render.size);
	else
		ft_calc_points(&data->map, data->map.polar, data->render.size);
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
	t = clock() - t;
	ret = (double)t / CLOCKS_PER_SEC;
	printf("TIME: %f\n", ret * 1000);
	return (0);
}

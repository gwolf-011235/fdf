/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/01 17:03:51 by gwolf            ###   ########.fr       */
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

void	ft_calc_points(t_map *map, t_mat4 mat, int sum, int size[2])
{
	int		i;

	i = 0;
	while (i < sum)
	{
 		map->morph[i] = ft_mult_vec3f_mat4(map->points[i], mat);
		map->morph[i].color = map->points[i].color;
		map->morph[i].hidden = ft_is_outside(map->morph[i], size, 0);
		i++;
	}
}

void	ft_init_project(t_map *map, int size[2])
{
	map->props.scale = ft_fit_box(map->edges, map->mat, map->props);
	ft_calc_points(map, map->mat, map->sum_points, size);
}

void	ft_redraw(t_data *data)
{
	ft_build_transmat(data->map.mat, data->map.props);
	ft_calc_points(&data->map, data->map.mat, data->map.sum_points, data->render.size);
	fill_background(&data->render, data->map.pattern[3]);
	lines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
}

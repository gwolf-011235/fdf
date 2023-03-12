/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/12 07:30:32 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_project(t_data *data)
{
	t_map	*map;

	map = &data->map;
	ft_scale_z(map->points, map->z_storage, map->sum_points, 0.1);
	map->props.scale = ft_fit_box(map->edges, map->mat, map->props);
	ft_calc_morph(map->morph, map->points, map->mat, map);
	ft_set_morph_color(map->morph, map->points, map->sum_points);
	ft_wirelines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
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
		if (morph[i].x < 0 || morph[i].x > map->props.canvas[X]
			|| morph[i].y < 0 || morph[i].y > map->props.canvas[Y])
			morph[i].hidden = true;
		else
			morph[i].hidden = false;
		i++;
	}
}

int	ft_render(t_data *data)
{
	clock_t			t;
	double			ret;
	t_map			*map;
	static uint64_t	last_update;

	if (ft_timestamp_ms(&data->render) - last_update < (uint64_t)(1000 / 30))
		return (0);
	last_update = ft_timestamp_ms(&data->render);
	printf("TIME: %ld\n", last_update);
	map = &data->map;
	t = clock();
	fill_background(&data->render, data->map.pattern[3]);
	if (!map->props.sphere)
		data->calc_ft(map->morph, map->points, map->mat, map);
	else
		data->calc_ft(map->morph, map->polar, map->mat, map);
	if (data->map.rainbow)
		ft_skittles(&data->map, data->map.morph);
	data->draw_ft(&data->render, map);
	if (map->props.box)
		ft_draw_box(&data->render, map->corner[1]);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
	//mlx_put_image_to_window(data->mlx, data->win, data->menu.ptr, 0, 0);
	t = clock() - t;
	ret = (double)t / CLOCKS_PER_SEC;
	printf("TIME: %f\n", ret * 1000);
	return (0);
}

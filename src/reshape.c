/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf < gwolf@student.42vienna.com >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:22:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/31 11:10:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_projection(t_data *data)
{
	t_map	*map;

	map = &data->map;
	ft_set_morph_color(map->points, map->morph, map);
	map->props.scale = ft_fit_box(map->corner[0], map->mat, map->props);
	ft_calc_morph(map->morph, map->points, map->mat, map);
	ft_draw_wirelines(&data->render, &data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->render.ptr, 0, 0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:28:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/11 23:35:16 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_calc_edges(t_map *map)
{
	int i;

	map->edges = malloc(sizeof(t_vec3f) * 8);

	i = 0;
	while (i < 8)
	{
		if (i < 4)
			map->edges[i].y = map->max[Y];
		else
			map->edges[i].y = map->min[Y];
		if (i % 2)
			map->edges[i].x = map->max[X];
		else
			map->edges[i].x = map->min[X];
		if (i > 1 && i < 6)
			map->edges[i].z = map->low;
		else
			map->edges[i].z = map->top;
		i++;
	}
}

void	ft_draw_box(t_data *data)
{
	t_vec3f	*edges;
	t_vec2i	start;
	t_vec2i	end;
	int	i;
	int colors[2];

	colors[0] = create_trgb(0, 0, 0, 255);
	colors[1] = create_trgb(0, 0, 0, 255);

	edges = data->map.edges;
	i = 0;
	while (i < 8)
	{
		edges[i] = ft_mult_vec3f_mat4(edges[i], data->map.trans);
		i++;
	}
	start = ft_convert_3to2(edges[0]);
	end = ft_convert_3to2(edges[1]);
	if (!ft_is_outside(edges[0], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[1], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);
	end = ft_convert_3to2(edges[2]);
	if (!ft_is_outside(edges[0], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[2], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);
	end = ft_convert_3to2(edges[6]);
	if (!ft_is_outside(edges[0], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[6], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);

	start = ft_convert_3to2(edges[3]);
	end = ft_convert_3to2(edges[1]);
	if (!ft_is_outside(edges[3], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[1], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);
	end = ft_convert_3to2(edges[2]);
	if (!ft_is_outside(edges[3], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[2], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);
	end = ft_convert_3to2(edges[5]);
	if (!ft_is_outside(edges[3], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[5], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);

	start = ft_convert_3to2(edges[4]);
	end = ft_convert_3to2(edges[5]);
	if (!ft_is_outside(edges[4], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[5], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);
	end = ft_convert_3to2(edges[6]);
	if (!ft_is_outside(edges[4], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[6], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);
	end = ft_convert_3to2(edges[2]);
	if (!ft_is_outside(edges[4], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[2], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);

	start = ft_convert_3to2(edges[7]);
	end = ft_convert_3to2(edges[5]);
	if (!ft_is_outside(edges[7], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[5], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);
	end = ft_convert_3to2(edges[6]);
	if (!ft_is_outside(edges[7], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[6], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);
	end = ft_convert_3to2(edges[1]);
	if (!ft_is_outside(edges[7], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[1], data->render.win_x, data->render.win_y))
		draw_line(&data->render, start, end, colors);
}

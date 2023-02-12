/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:28:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/12 13:57:36 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_calc_edges(t_map *map)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (i == 1 || i == 2 || i == 5 || i == 6)
			map->edges[i].x = map->max[X];
		else
			map->edges[i].x = map->min[X];
		if (i == 2 || i == 3 || i == 6 || i == 7)
			map->edges[i].y = map->max[Y];
		else
			map->edges[i].y = map->min[Y];
		if (i < 4)
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


	edges = data->map.edges P;
	i = 0;
	while (i < 8)
	{
		printf("INIT\n");
		ft_print_point(edges[i - P]);
		edges[i] = ft_mult_vec3f_mat4(edges[i - P], data->map.trans);
		printf("MORPH\n");
		ft_print_point(edges[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		colors[0] = BLUE;
		colors[1] = BLUE;
		start = ft_convert_3to2(edges[i]);
		end = ft_convert_3to2(edges[((i) + 1) % 4]);
		if (!ft_is_outside(edges[i], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[((i) + 1) % 4], data->render.win_x, data->render.win_y))
			draw_line(&data->render, start, end, colors);
		colors[0] = RED;
		colors[1] = RED;
		end = ft_convert_3to2(edges[i + 4]);
		if (!ft_is_outside(edges[i], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[i + 4], data->render.win_x, data->render.win_y))
			draw_line(&data->render, start, end, colors);
		colors[0] = GREEN;
		colors[1] = GREEN;
		start = ft_convert_3to2(edges[i + 4]);
		end = ft_convert_3to2(edges[((i + 1) % 4) + 4]);
		if (!ft_is_outside(edges[i + 4], data->render.win_x, data->render.win_y) && !ft_is_outside(edges[((i + 1) % 4) + 4], data->render.win_x, data->render.win_y))
			draw_line(&data->render, start, end, colors);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:28:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/15 14:42:50 by gwolf            ###   ########.fr       */
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

float	ft_fit_box(t_vec3f *init, int size[2], int offset[2])
{
	float	scale;
	int		i;
	t_vec3f	temp;

	scale = 1;
	while (1)
	{
		i = 0;
		while (i < 8)
		{
			temp.x = (init[i].x * scale + offset[X]) * 1.2;
			temp.y = (init[i].y * scale + offset[Y]) * 1.2;
			if (temp.x > size[X] || temp.y > size[Y])
			{
				printf("Scale is: %f\n", scale);
				return (scale);
			}
			i++;
		}
		scale += 0.1;
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
		edges[i] = ft_mult_vec3f_mat4(edges[i - P], data->map.trans);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		colors[0] = BLUE;
		colors[1] = BLUE;
		start = ft_convert_3to2(edges[i]);
		end = ft_convert_3to2(edges[((i) + 1) % 4]);
		if (!ft_is_outside(edges[i], data->render.size[X], data->render.size[Y]) && !ft_is_outside(edges[((i) + 1) % 4], data->render.size[X], data->render.size[Y]))
			draw_line(&data->render, start, end, colors);
		colors[0] = RED;
		colors[1] = RED;
		end = ft_convert_3to2(edges[i + 4]);
		if (!ft_is_outside(edges[i], data->render.size[X], data->render.size[Y]) && !ft_is_outside(edges[i + 4], data->render.size[X], data->render.size[Y]))
			draw_line(&data->render, start, end, colors);
		colors[0] = GREEN;
		colors[1] = GREEN;
		start = ft_convert_3to2(edges[i + 4]);
		end = ft_convert_3to2(edges[((i + 1) % 4) + 4]);
		if (!ft_is_outside(edges[i + 4], data->render.size[X], data->render.size[Y]) && !ft_is_outside(edges[((i + 1) % 4) + 4], data->render.size[X], data->render.size[Y]))
			draw_line(&data->render, start, end, colors);
		i++;
	}
}

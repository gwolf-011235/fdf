/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:28:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/17 09:27:07 by gwolf            ###   ########.fr       */
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
			map->edges[i + i].x = map->max[X];
		else
			map->edges[i + i].x = map->min[X];
		if (i == 2 || i == 3 || i == 6 || i == 7)
			map->edges[i + i].y = map->max[Y];
		else
			map->edges[i + i].y = map->min[Y];
		if (i < 4)
			map->edges[i + i].z = map->min[Z];
		else
			map->edges[i + i].z = map->max[Z];
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
			temp.x = (init[i + i].x * scale + offset[X]) * 1.2;
			temp.y = (init[i + i].y * scale + offset[Y]) * 1.2;
			if (temp.x > size[X] || temp.y > size[Y])
			{
				scale = floor(scale);
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
	t_point	*edges;
	t_point	start;
	t_point	end;
	int	i;

	edges = data->map.pixel + data->map.sum_points;
	i = 0;
	while (i < 4)
	{
		start = edges[i];
		end = edges[(i + 1) % 4];
		start.color = BLUE;
		end.color = BLUE;
		if (ft_is_inside(start, data->render.size[X], data->render.size[Y]) && ft_is_inside(end, data->render.size[X], data->render.size[Y]))
			draw_line(&data->render, start, end);
		end = edges[i + 4];
		start.color = RED;
		end.color = RED;
		if (ft_is_inside(start, data->render.size[X], data->render.size[Y]) && ft_is_inside(end, data->render.size[X], data->render.size[Y]))
			draw_line(&data->render, start, end);
		start = edges[i + 4];
		end = edges[((i + 1) % 4) + 4];
		start.color = GREEN;
		end.color = GREEN;
		if (ft_is_inside(start, data->render.size[X], data->render.size[Y]) && ft_is_inside(end, data->render.size[X], data->render.size[Y]))
			draw_line(&data->render, start, end);
		i++;
	}
}

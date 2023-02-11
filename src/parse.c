/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:33 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/11 21:55:59 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map_alloc(t_map *map)
{
	map->points = malloc(sizeof(t_vec3f) * map->sum_points * 2);
	map->color_array = malloc(sizeof(int) * map->sum_points);
	if (!map->points || !map->color_array)
		terminate(ERR_MEM);
	map->morph = &map->points[1];
	ft_bzero(map->color_array, sizeof(int) * map->sum_points);
}

void	ft_parse_line(t_map *map, char *line, int index)
{
	int	i;
	int len_hex;

	i = 0;
	while (line[i])
	{
		map->points[index + index].x = (index % map->width) + map->min[X];
		map->points[index + index].y = (index / map->width) + map->min[Y];
		map->points[index + index].z = ft_atoi(&line[i]);
		ft_find_extremes(map, map->points[index + index].z);
		i += ft_move_atoi(&line[i]);
		if (map->hex && line[i] == ',')
		{
			len_hex = ft_jump_over_hex(&line[i]);
			map->color_array[index] = ft_hex_to_decimal(&line[i + 3], len_hex);
			i += len_hex;
		}
		index++;
		if (line[i] == '\n')
			break ;
	}
	free(line);
}

void	ft_set_colors(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->sum_points)
	{
		if (map->hex)
		{
			if (!map->color_array[i])
				map->color_array[i] = map->color_mid;
			i++;
			continue ;
		}
		if (map->points[i + i].z == 0)
			map->color_array[i] = map->color_mid;
		else if (map->points[i + i].z > 0)
			map->color_array[i] = gradient(map->color_mid, map->color_top, map->top, map->points[i + i].z);
		else
			map->color_array[i] = gradient(map->color_mid, map->color_low, map->low, map->points[i + i].z);
		i++;
	}
}

void	ft_parse_map(t_map *map)
{
	int i;

	ft_map_alloc(map);
	map->min[X] = -(map->width / 2);
	map->min[Y] = -(map->height / 2);
	map->max[X] = map->min[X] * -1;
	map->max[Y] = map->min[Y] * -1;
	if (!map->width % 2)
		map->max[X]--;
	if (!map->height % 2)
		map->max[Y]--;
	i = 0;
	while (i < map->height)
	{
		ft_parse_line(map, map->rows[i], i * map->width);
		i++;
	}
	ft_set_colors(map);
	ft_calc_edges(map);
}

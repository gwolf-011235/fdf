/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:33 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/08 15:47:29 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_alloc(t_map *map)
{
	map->points = malloc(map->sum_points * sizeof(t_point) * 2);
	map->color_array = malloc(map->sum_points * sizeof(int));
	if (!map->points || !map->color_array)
		terminate(ERR_MEM);
	map->morph = map->points + map->sum_points;
}

void	ft_convert_line(t_map *map, char *line, int index)
{
	int	i;

	i = 0;
	while (line[i])
	{
		map->points[index].x = (index % map->width) - (map->width / 2);
		map->points[index].y = (index / map->width) - (map->height / 2);
		map->points[index].z = ft_atoi(&line[i]);
		ft_find_extremes(map, map->points[index].z);
		while (line[i] == ' ')
			i++;
		if (line[i] == '-' && ft_isdigit(line[i + 1]))
			i++;
		while (ft_isdigit(line[i]))
			i++;
		if (map->hex && line[i] == ',')
			i += ft_jump_over_hex(&line[i]);
		index++;
		if (line[i] == '\n')
			break ;
	}
	free(line);
}

void	fetch_points(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		ft_convert_line(map, map->rows[i], i * map->width);
		i++;
	}
}

void	ft_set_colors(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->sum_points)
	{
		if (map->points[i].z == 0)
			map->color_array[i] = map->color_mid;
		else if (map->points[i].z > 0)
			map->color_array[i] = gradient(map->color_mid, map->color_top, map->top, map->points[i].z);
		else
			map->color_array[i] = gradient(map->color_mid, map->color_low, map->low, map->points[i].z);
		i++;
	}
}

void	parse_map(t_map *map)
{
	map_alloc(map);
	fetch_points(map);
	ft_bzero(map->color_array, map->sum_points * sizeof(int));
	ft_set_colors(map);
}

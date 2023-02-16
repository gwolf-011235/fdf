/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:33 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/16 17:50:17 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map_alloc(t_map *map)
{
	map->points = malloc(sizeof(t_vec3f) * (map->sum_points * 2 + 16));
	if (!map->points)
		ft_terminate(ERR_MEM);
	map->colors = malloc(sizeof(int) * map->sum_points);
	if (!map->colors)
	{
		free(map->points);
		ft_terminate(ERR_MEM);
	}
	map->morph = &map->points[1];
	map->edges = &map->points[map->sum_points * 2];
	ft_bzero(map->colors, sizeof(int) * map->sum_points);
}

void	ft_parse_line(t_map *map, char *line, int i)
{
	int	j;
	int	len_hex;

	j = 0;
	while (line[j])
	{
		map->points[i D].x = (i % map->width) + map->min[X];
		map->points[i D].y = (i / map->width) + map->min[Y];
		map->points[i D].z = ft_atoi(&line[j]);
		ft_find_extremes(map, map->points[i D].z);
		j += ft_move_atoi(&line[j]);
		if (map->hex && line[j] == ',')
		{
			len_hex = ft_jump_over_hex(&line[j]);
			map->colors[i] = ft_hex_to_decimal(&line[j + 3], len_hex);
			j += len_hex;
		}
		i++;
		if (line[j] == '\n')
			break ;
	}
	free(line);
}

void	ft_set_colors(t_map *map, t_vec3f *points, int *colors)
{
	int	i;

	i = 0;
	while (i < map->sum_points)
	{
		if (map->hex)
		{
			if (!colors[i])
				colors[i] = map->color_mid;
			i++;
			continue ;
		}
		if (map->points[i + i].z == 0)
			map->colors[i] = map->color_mid;
		else if (map->points[i + i].z > 0)
			map->colors[i] = gradient(map->color_mid, map->color_top, map->top, map->points[i + i].z);
		else
			map->colors[i] = gradient(map->color_mid, map->color_low, map->low, map->points[i + i].z);
		i++;
	}
}

void	ft_parse_map(t_map *map)
{
	int	i;

	ft_map_alloc(map);
	map->min[X] = -(map->width / 2);
	map->min[Y] = -(map->height / 2);
	map->max[X] = map->min[X] * -1;
	map->max[Y] = map->min[Y] * -1;
	if (!(map->width % 2))
		map->max[X]--;
	if (!(map->height % 2))
		map->max[Y]--;
	i = 0;
	while (i < map->height)
	{
		ft_parse_line(map, map->rows[i], i * map->width);
		i++;
	}
	ft_set_colors(map, map->points, map->colors);
	ft_calc_edges(map);
}

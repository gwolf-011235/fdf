/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:33 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/16 17:19:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_parse_map(t_map *map)
{
	int	i;

	ft_map_alloc(map);
	ft_set_limits_xy(map);
	i = 0;
	while (i < map->height)
	{
		ft_parse_line(map, map->rows[i], i * map->width);
		i++;
	}
	ft_find_limits_z(map);
	ft_fill_z_storage(map);
	ft_set_colors(map, map->points);
	ft_set_corners(map->corner[0], map->limits);
	ft_set_ang_coords(map, map->sum_points);
}

void	ft_map_alloc(t_map *map)
{
	map->points = malloc(sizeof(t_vec3f) * (map->sum_points * 3 + 24));
	map->z_storage = malloc(sizeof(int) * (map->sum_points + 8));
	map->ang_coord = malloc(sizeof(t_coord) * map->sum_points);
	if (!map->points || !map->z_storage || !map->ang_coord)
	{
		ft_free_map_ptr(map, ERR_MEM);
	}
	map->corner[0] = map->points + map->sum_points;
	map->morph = map->corner[0] + 8;
	map->corner[1] = map->morph + map->sum_points;
	map->polar = map->corner[1] + 8;
	map->corner[2] = map->polar + map->sum_points;
}

void	ft_parse_line(t_map *map, char *line, int i)
{
	int	j;
	int	len_hex;

	j = 0;
	while (line[j])
	{
		map->points[i].x = ((i % map->width) + map->limits[XMIN]);
		map->points[i].y = ((i / map->width) + map->limits[YMIN]);
		map->points[i].z = ft_atoi(&line[j]);
		j += ft_move_atoi(&line[j]);
		if (map->hex && line[j] == ',')
		{
			len_hex = ft_jump_over_hex(&line[j]);
			map->points[i].color = ft_hex_to_dec(&line[j + 3], len_hex - 3);
			j += len_hex;
		}
		else
			map->points[i].color = 0x0;
		i++;
		if (line[j] == '\n')
			break ;
	}
	free(line);
}

void	ft_set_colors(t_map *map, t_vec3f *points)
{
	int	i;
	int	*pattern;

	pattern = map->pattern;
	i = 0;
	while (i < map->sum_points)
	{
		if (map->hex)
		{
			if (!points[i].color)
				points[i].color = pattern[1];
			i++;
			continue ;
		}
		if (points[i].z == 0)
			points[i].color = pattern[1];
		else if (points[i].z > 0)
			points[i].color = ft_gradient(pattern[1], pattern[2], \
					map->limits[ZMAX], points[i].z);
		else
			points[i].color = ft_gradient(pattern[1], pattern[0], \
					map->limits[ZMIN], points[i].z);
		i++;
	}
}

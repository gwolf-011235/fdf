/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:33 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/01 15:00:36 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_count_num(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '-' && ft_isdigit(line[i + 1]))
			i++;
		while (ft_isdigit(line[i]))
			i++;
		count++;
		if (line[i] != ' ' || line[i] == '\n')
			break ;
	}
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (count);
	else
		return (-1);
}

void	map_alloc(t_map *map, int fd)
{
	int	num_rows;
	char *row;

	num_rows = 0;
	row = get_next_line(fd);
	if (!row)
		terminate(ERR_EMPTY);
	while (row)
	{
		if (num_rows == ROW_MAX)
			terminate(ERR_BIG);
		map->rows[num_rows++] = row;
		row = get_next_line(fd);
	}
	map->height = num_rows;
	map->width = ft_count_num(map->rows[0]);
	if (map->width == -1)
		terminate(ERR_READ);
	map->points = malloc(map->height * map->width * sizeof(t_point));
	if (!map->points)
		terminate(ERR_MEM);
}

void	ft_convert_line(t_map *map, char *line, int index)
{
	int i;

	i = 0;
	while (line[i])
	{
		map->points[index].x = (index % map->width) - (map->width / 2);
		map->points[index].y = (index / map->width) - (map->height / 2);
		map->points[index].z = ft_atoi(&line[i]);
		while (line[i] == ' ')
			i++;
		if (line[i] == '-' && ft_isdigit(line[i + 1]))
			i++;
		while (ft_isdigit(line[i]))
			i++;
		index++;
		while (line[i] == ' ')
			i++;
		if (line[i] == '\n')
			break ;
	}
	free(line);
}

void	fetch_points(t_map *map)
{
	int i;

	i = 0;
	while (i < map->height)
	{
		if (ft_count_num(map->rows[i]) != map->width)
			terminate(ERR_LINE);
		ft_convert_line(map, map->rows[i], i * map->width);
		i++;
	}
}

void	parse_map(t_map *map, char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		terminate(ERR_OPEN);
	map_alloc(map, fd);
	if (close(fd) == -1)
		terminate(ERR_CLOSE);
	fetch_points(map);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:54:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/26 18:30:57 by gwolf            ###   ########.fr       */
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
	if (close(fd) == -1)
		terminate(ERR_CLOSE);
	map->height = num_rows;
	map->width = ft_count_num(map->rows[0]);
	if (map->width == -1)
		terminate(ERR_READ);
	map->array = malloc(map->height * map->width * sizeof(int));
	if (!map->array)
		terminate(ERR_MEM);
}

void	ft_convert_line(t_map *map, char *line, int i)
{
	int index;

	index = i * map->width;
	i = 0;
	while (line[i])
	{
		map->array[index] = ft_atoi(&line[i]);
		while (line[i] == ' ')
			i++;
		if (line[i] == '-' && ft_isdigit(line[i + 1]))
			i++;
		while (ft_isdigit(line[i]))
			i++;
		index++;
		if (line[i] == '\n')
			break ;
	}
	free(line);
}

void	fill_array(t_map *map)
{
	int i;

	i = 0;
	while (i < map->height)
	{
		if (ft_count_num(map->rows[i]) != map->width)
			terminate(ERR_LINE);
		ft_convert_line(map, map->rows[i], i);
		i++;
	}
}

void	ft_print_map(t_map *map)
{
	int i;

	i = 0;
	while (i < (map->height * map->width))
	{
		ft_printf("%03d ", map->array[i]);
		i++;
		if (i % map->width == 0)
			ft_printf("\n");
	}
}

int main(int argc, char *argv[])
{
	int fd;

	if (argc != 2)
		terminate(ERR_ARGS);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		terminate(ERR_OPEN);

	t_map map;

	map_alloc(&map, fd);
	fill_array(&map);
	ft_print_map(&map);
}

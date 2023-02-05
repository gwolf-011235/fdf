/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 21:36:25 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/05 22:09:00 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_count_num(char *line)
{
	int	i;
	int	count;

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
		if (line[i] == ',')
			i += ft_jump_over_hex(&line[i]);
		if (line[i] != ' ' || line[i] == '\n')
			break ;
	}
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (count);
	else
		return (-1);
}

int	ft_jump_over_hex(char *line)
{
	int		i;
	bool	big;

	i = 0;
	if (line[i] == ',' && line[i + 1] == '0')
		i += 2;
	else
		return (-1);
	if (line[i] == 'x')
		big = false;
	else if (line[i] == 'X')
		big = true;
	else
		return (-1);
	i++;
	while (big && ft_strchr("0123456789ABCDEF", line[i]))
		i++;
	while (!big && ft_strchr("0123456789abcdef", line[i]))
		i++;
	if (line[i] == ' ')
		return (i);
	else
		return (-1);
}

void	ft_check_row(t_map *map, char *row)
{
	int	count;

	count = ft_count_num(row);
	if (count != map->width)
	{
		ft_printf("Line %d is bad!\n", map->height);
		ft_printf("Expected: %d\n", map->width);
		ft_printf("Got: %d\n", count);
		free(row);
		terminate(ERR_LINE);
	}
}

void	ft_extract_rows(t_map *map, int fd)
{
	char	*row;

	row = get_next_line(fd);
	if (!row)
		terminate(ERR_EMPTY);
	map->width = ft_count_num(row);
	if (map->width == -1)
	{
		free(row);
		terminate(ERR_READ);
	}
	while (row)
	{
		if (map->height == ROW_MAX)
			terminate(ERR_BIG);
		map->rows[map->height++] = row;
		row = get_next_line(fd);
		if (!row)
			break ;
		ft_check_row(map, row);
	}
	map->sum_points = map->height * map->width;
}

void	ft_validate_map(t_map *map, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		terminate(ERR_OPEN);
	ft_extract_rows(map, fd);
	if (close(fd) == -1)
		terminate(ERR_CLOSE);
}

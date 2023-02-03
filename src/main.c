/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:54:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/03 09:21:00 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map_init(t_map *map)
{
	map->ang_x = 30;
	map->ang_y = 330;
	map->ang_z = 30;
	map->scale = 30;
	map->offset_x = (WIN_X / 2);
	map->offset_y = (WIN_Y / 2);
	map->top = 0;
	map->low = 0;
}

int main(int argc, char *argv[])
{
	static t_data data;

	if (argc != 2)
		terminate(ERR_ARGS);

	parse_map(&data.map, argv[1]);
	ft_copy_map(&data.map);

	ft_shape_map(&data.map);

	testwindow(&data);
}

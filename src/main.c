/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:54:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/17 09:54:32 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	static t_data	data;
	t_map			*map;

	map = &data.map;
	if (argc != 2)
		ft_terminate(ERR_ARGS);
	ft_map_init(&data.map);
	ft_check_map(&data.map, argv[1]);
	ft_parse_map(&data.map);
	ft_init_window(&data);
	map->scale = ft_fit_box(map->edges, data.render.size, map->offset);
	ft_init_project(&data.map);
	//test(&data);
	//ft_shape_map(&data.map);
	testwindow(&data);
}

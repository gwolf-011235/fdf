/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:54:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/02 14:53:40 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char *argv[])
{
	static t_data data;

	if (argc != 2)
		terminate(ERR_ARGS);

	parse_map(&data.map, argv[1]);
	ft_copy_map(&data.map);

	data.map.ang_x = 30;
	data.map.ang_y = 330;
	data.map.ang_z = 30;
	data.map.scale = 30;
	data.map.offset_x = (WIN_X / 2);
	data.map.offset_y = (WIN_Y / 2);
	ft_shape_map(&data.map);

	testwindow(&data);
}

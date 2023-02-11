/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:54:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/11 15:44:05 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	static t_data	data;

	if (argc != 2)
		terminate(ERR_ARGS);
	ft_map_init(&data.map);
	ft_validate_map(&data.map, argv[1]);
	ft_parse_map(&data.map);
	ft_init_window(&data);
	//test(&data);
	ft_shape_map(&data.map);
	testwindow(&data);
}

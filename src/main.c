/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:54:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/05 21:47:18 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char *argv[])
{
	static t_data data;

	test();
	if (argc != 2)
		terminate(ERR_ARGS);

	ft_map_init(&data.map);
	ft_validate_map(&data.map, argv[1]);
	parse_map(&data.map);
	ft_copy_map(&data.map);

	ft_shape_map(&data.map);

	testwindow(&data);
}

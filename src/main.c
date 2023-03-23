/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:54:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 15:25:19 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	static t_data	data;

	if (argc != 2)
		ft_terminate(ERR_ARGS);
	ft_check_map(&data.map, argv[1]);
	ft_init_data(&data);
	ft_parse_map(&data.map);
	ft_init_window(&data);
	ft_init_projection(&data);
	ft_start_mlx_loop(&data);
}
